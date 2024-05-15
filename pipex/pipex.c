/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:24 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/13 14:20:26 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		ft_free1(data->path);
		exit(126);
	}
	return (fd);
}

void	child_process(t_data *data, char **av, char **env)
{
	int		fd;
	char	*p;

	data->pid = fork();
	if (data->pid == -1)
	{
		ft_free1(data->path);
		exit(1);
	}
	if (data->pid == 0)
	{
		fd = check_file(data, av[1]);
		data->cmd1 = ft_split(av[2], ' ');
		p = check_path(data, data->cmd1);
		dup2(fd, 0);
		dup2(data->pipe[1], 1);
		close(data->pipe[1]);
		close(fd);
		close(data->pipe[0]);
		if (execve(p, data->cmd1, env) == -1)
			print_error(p, data, data->cmd1);
	}
}

void	child2_process(t_data *data, char **av, char **env)
{
	char	*p;
	int		fd;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[4]);
		ft_free1(data->path);
		exit(1);
	}
	data->cmd2 = ft_split(av[3], ' ');
	p = check_path(data, data->cmd2);
	dup2(fd, 1);
	dup2(data->pipe[0], 0);
	close(fd);
	close(data->pipe[0]);
	close(data->pipe[1]);
	if (execve(p, data->cmd2, env) == -1)
		print_error(p, data, data->cmd2);
}

void	ft_wait(t_data *data)
{
	int	a;

	close(data->pipe[0]);
	close(data->pipe[1]);
	waitpid(data->pid, &data->status, 0);
	waitpid(data->pid1, &data->status, 0);
	ft_free1(data->path);
	a = data->status >> 8;
	exit(a);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
	{
		write(1, "please 4 argemant\n", 19);
		return (0);
	}
	data.pth = ft_path("PATH=", envp);
	data.pth = ft_skip("PATH=", data.pth);
	data.path = ft_split(data.pth, ':');
	if (pipe(data.pipe) == -1)
	{
		ft_free1(data.path);
		exit(1);
	}
	child_process(&data, av, envp);
	data.pid1 = fork();
	if (data.pid1 == -1)
	{
		ft_free1(data.path);
		exit(1);
	}
	if (data.pid1 == 0)
		child2_process(&data, av, envp);
	ft_wait(&data);
}
