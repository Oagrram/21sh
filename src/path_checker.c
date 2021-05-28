/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:17:23 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:17:25 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	char	*find_path(char **tabs)
{
	int i;

	i = 0;
	while (tabs[i])
	{
		if (ft_strncmp(tabs[i], "PATH=", 5) == 0)
			return (tabs[i]);
		i++;
	}
	return (NULL);
}

char			*valid_path(char *cmd_name, char **tabs)
{
	char	*p;
	char	*str1;
	char	*str2;
	char	**path;
	int		i;

	i = -1;
	if (!(p = find_path(tabs)) || !tabs)
		return (NULL);
	path = ft_strsplit(&p[5], ':');
	while (path[++i])
	{
		str1 = ft_strjoin(path[i], "/");
		str2 = ft_strjoin(str1, cmd_name);
		ft_strdel(&str1);
		if (access(str2, F_OK) == 0)
		{
			free_tabs(path);
			return (str2);
		}
		ft_strdel(&str2);
	}
	free_tabs(path);
	return (NULL);
}
