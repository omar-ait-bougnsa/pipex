/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:19 by oait-bou          #+#    #+#             */
/*   Updated: 2024/05/13 15:18:43 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free1(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	dest[len++] = '/';
	while (src[i] != '\0')
	{
		dest[len] = src[i];
		i++;
		len++;
	}
	dest[len] = '\0';
	return (dest);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

char	*ft_skip(char *str, char *path)
{
	int	i;

	i = 0;
	if (path == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == path[i])
			i++;
		else
			break ;
	}
	return (&path[i]);
}

char	*ft_path(char *s1, char **env)
{
	int	i;
	int	j;

	j = 0;
	if (env[0] == NULL)
		return (NULL);
	while (env[j])
	{
		i = 0;
		while (s1[i])
		{
			if (s1[i] != env[j][i])
				break ;
			i++;
		}
		if (s1[i] == '\0')
			return (env[j]);
		j++;
	}
	return (NULL);
}
