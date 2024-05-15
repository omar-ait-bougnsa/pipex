/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:12:45 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/13 14:20:59 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

void	print_error(char *p, t_data *data, char **cmd)
{
	perror(p);
	ft_free1(data->path);
	ft_free1(cmd);
	exit(126);
}

void	ft_free_exit(char *str, t_data *data, int n, char **cmd)
{
	ft_putstr(str);
	str = NULL;
	ft_free1(data->path);
	if (cmd[0] == NULL)
		free(cmd);
	else
		ft_free1(cmd);
	exit(n);
}

int	ft_check_access(t_data *data, char **cmd)
{
	if (access(cmd[0], F_OK) != -1)
	{
		data->fd = open(cmd[0], O_CREAT);
		if (access(cmd[0], X_OK) == -1 || data->fd == -1)
		{
			perror(cmd[0]);
			ft_free1(data->path);
			ft_free1(cmd);
			if (data->fd != -1)
				close(data->fd);
			exit(126);
		}
		close(data->fd);
	}
	else
	{
		perror(cmd[0]);
		ft_free1(data->path);
		ft_free1(cmd);
		exit(127);
	}
	return (1);
}

char	*check_path(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == NULL)
		ft_free_exit(": : command not found\n", data, 127, cmd);
	if (cmd[0][0] == '.' && cmd[0][1] == '\0')
		ft_free_exit(".: filename argument required\n", data, 2, cmd);
	if (ft_strchr(cmd[0], '/') != 0 || data->path[0] == NULL)
	{
		if (ft_check_access(data, cmd) == 1)
			return (cmd[0]);
	}
	while (data->path[i])
	{
		data->pth = ft_strjoin(data->path[i++], cmd[0]);
		if (access(data->pth, X_OK) == 0)
			return (data->pth);
		free(data->pth);
	}
	if (data->path[i] == NULL)
	{
		ft_putstr(cmd[0]);
		ft_free_exit(" : command not found\n", data, 127, cmd);
	}
	return (NULL);
}
