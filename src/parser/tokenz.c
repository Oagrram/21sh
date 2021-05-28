/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:14 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:21:15 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	int		ft_next_token2(char **line, int *i, t_token **tok)
{
	int			j;
	char		*tmp;
	t_token		*token;
	t_token_v	v;

	j = 0;
	v.k = *i;
	v.str = *line;
	token = *tok;
	if (!(tmp = ft_strnew(1024)))
		return (1);
	while (v.str[v.k] && !is_white(v.str[v.k]) &&
			!ft_is_there("'\";|><", v.str[v.k]))
		tmp[j++] = v.str[v.k++];
	if (v.str[v.k] == '\'' || v.str[v.k] == '"')
		v.k = ft_quotes(line, v.k, &tmp);
	if (v.str[v.k] == '>' || v.str[v.k] == '<')
		ft_check_fd(&tmp, &token, 0);
	else if (i[1] && !(i[1] = 0))
		ft_check_fd(&tmp, &token, 1);
	else if (tmp[0])
		ft_check_word(&token, &tmp);
	free(tmp);
	*i = v.k;
	return (1);
}

int				ft_next_token(char **line, t_token **tok, int mode)
{
	char		*str;
	static	int	i[2] = {0, 0};

	if (!mode && !(i[1] = 0))
		return (i[0] = 0);
	if (!(*tok = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	str = *line;
	while (str[i[0]])
	{
		if (str[i[0]] == ';' || str[i[0]] == '|')
		{
			i[0] = ft_separators(tok, str, i[0]);
			return (1);
		}
		else if (str[i[0]] == '<' || str[i[0]] == '>' || str[i[0]] == '&')
			return (i[0] = ft_redirection(str, tok, i[0], &i[1]));
		else if (str[i[0]] && !is_white(str[i[0]]))
			return (ft_next_token2(line, i, tok));
		else
			i[0]++;
	}
	*line = str;
	return (0);
}
