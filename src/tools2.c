/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:18:10 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:18:12 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char		*free_tabs(char **arg)
{
	char	**tabs;
	int		i;

	tabs = arg;
	i = -1;
	if (!tabs)
		return (NULL);
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
	return (NULL);
}

void		free_str(char *ptr, char *tmp)
{
	ft_strdel(&ptr);
	ft_strdel(&tmp);
}

char		*ft_changedir(char *str, char *cwd)
{
	char	*var;
	char	*path;

	var = ft_strjoin(cwd, "/");
	path = ft_strjoin(var, str);
	ft_strdel(&var);
	return (path);
}

int			free_tabs2(char **args, char **arr)
{
	if (args)
		free_tabs(args);
	if (arr)
		free_tabs(arr);
	return (1);
}

int			is_special(char c)
{
	if (c == '#' || c == '/' || c == '~' || c == '@'
		|| c == '^' || c == '$')
		return (1);
	return (0);
}
