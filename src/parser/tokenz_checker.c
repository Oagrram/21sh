/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:20 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:21:22 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_separators(t_token **tok, char *str, int i)
{
	t_token	*token;

	token = *tok;
	token->value = ft_strsub(str, i, 1);
	if (str[i] == ';')
		token->type = SEPARATEUR;
	else if (str[i] == '|')
		token->type = PIPE;
	return (i + 1);
}

int		is_white(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int		ft_is_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_fd(char **tmp, t_token **token, int mode)
{
	t_token		*tok;

	tok = *token;
	if (ft_is_numeric(*tmp) && !mode)
		tok->type = L_FD;
	else if (mode)
		tok->type = R_FD;
	else
		tok->type = WORD;
	tok->value = ft_strdup(*tmp);
	return (1);
}

int		ft_check_word(t_token **token, char **tmp)
{
	t_token	*tok;
	char	*str;

	tok = *token;
	str = *tmp;
	tok->value = ft_strdup(str);
	tok->type = WORD;
	return (1);
}
