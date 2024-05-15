/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:09 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/12 10:15:10 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;

	if (ac <= 4)
	{
		write(1, "command like this: file1 cmd1 cmd2 ... cmdn file2\n", 51);
		return (0);
	}
	data.pth = ft_path("PATH=", env);
	data.pth = ft_skip("PATH=", data.pth);
	data.path = ft_split(data.pth, ':');
	data.nbr_cmd = ac - 3;
	data.ac = ac;
	i = 0;
	while (i < data.nbr_cmd)
	{
		ft_execut_command(&data, i, av, env);
		i++;
	}
	i = 0;
	while (i < data.nbr_cmd)
		waitpid(data.pids[i++], &data.status, 0);
	ft_free1(data.path);
	i = data.status >> 8;
	exit(i);
}
