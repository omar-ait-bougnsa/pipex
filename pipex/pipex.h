/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:53:25 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/12 18:57:22 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_data
{
	int		fd;
	int		fd1;
	int		pipe[2];
	char	**path;
	char	*pth;
	char	**cmd;
	char	**cmd1;
	char	**cmd2;
	int		nbr_cmd;
	int		input;
	char	*envp;
	int		status;
	pid_t	pid;
	pid_t	pid1;
	pid_t	pids[1024];
	char	**av;
	int		ac;
	char	*str;
}			t_data;
char		**ft_split(char *s, char c);
void		ft_putstr(char *str);
void		child_process(t_data *data, char **av, char **env);
char		*ft_skip(char *str, char *path);
char		*ft_path(char *s1, char **env);
char		*check_path(t_data *data, char **cmd);
void		ft_free1(char **str);

char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
void		ft_execut_command(t_data *data, int i, char **av, char **env);
void		print_error(char *p, t_data *data, char **cmd);
int			check_file(t_data *data, char *file);
void		*ft_memcpy(void *dest, const void *src, size_t size);
#endif