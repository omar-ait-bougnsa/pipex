/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilis_bon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:13 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/13 11:40:43 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(t_data data, int i, char **env)
{
	data.fd = open(data.av[1], O_RDONLY);
	if (data.fd == -1)
	{
		perror(data.av[1]);
		ft_free1(data.path);
		exit(1);
	}
	data.cmd = ft_split(data.av[i + 2], ' ');
	data.pth = check_path(&data, data.cmd);
	dup2(data.fd, 0);
	dup2(data.pipe[1], 1);
	close(data.fd);
	close(data.pipe[0]);
	close(data.pipe[1]);
	if (execve(data.pth, data.cmd, env) == -1)
		print_error(data.pth, &data, data.cmd);
}

void	ft_child(t_data data, int i, char **env)
{
	data.cmd = ft_split(data.av[i + 2], ' ');
	data.pth = check_path(&data, data.cmd);
	dup2(data.input, STDIN_FILENO);
	dup2(data.pipe[1], STDOUT_FILENO);
	close(data.input);
	close(data.pipe[0]);
	close(data.pipe[1]);
	if (execve(data.pth, data.cmd, env) == -1)
		print_error(data.pth, &data, data.cmd);
}

void	ft_end_child(t_data data, int i, char **env)
{
	data.fd1 = open(data.av[data.ac - 1], O_CREAT | O_WRONLY | O_TRUNC);
	if (data.fd1 == -1)
	{
		perror(data.av[data.ac - 1]);
		ft_free1(data.path);
		exit(1);
	}
	data.cmd = ft_split(data.av[i + 2], ' ');
	data.pth = check_path(&data, data.cmd);
	dup2(data.input, STDIN_FILENO);
	dup2(data.fd1, STDOUT_FILENO);
	close(data.input);
	close(data.pipe[1]);
	close(data.fd1);
	if (execve(data.pth, data.cmd, env) == -1)
		print_error(data.pth, &data, data.cmd);
}

void	ft_execute_child(t_data data, int i, char **av, char **env)
{
	data.av = av;
	if (i == 0)
	{
		ft_first_child(data, i, env);
	}
	else if (i < data.nbr_cmd - 1)
	{
		ft_child(data, i, env);
	}
	else
		ft_end_child(data, i, env);
}

void	ft_execut_command(t_data *data, int i, char **av, char **env)
{
	if (i != data->nbr_cmd - 1)
	{
		if ((pipe(data->pipe)) == -1)
		{
			ft_free1(data->path);
			exit(1);
		}
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		ft_free1(data->path);
		exit(1);
	}
	if (data->pids[i] == 0)
		ft_execute_child(*data, i, av, env);
	else
	{
		if (i != 0)
			close(data->input);
		data->input = data->pipe[0];
		if (i < data->nbr_cmd - 1)
			close(data->pipe[1]);
	}
}
