/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:28 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:21:30 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	int		ft_redir_o(char *str, t_token **tok, int i)
{
	t_token *token;

	token = *tok;
	if (str[i + 1] == '&')
	{
		token->type = AGGREGATION_OUT;
		i++;
	}
	else if (str[i + 1] == '>')
	{
		token->type = APPEND_OUT;
		i++;
	}
	else
		token->type = REDIR_OUT;
	return (i);
}

static int		ft_redir_i(char *str, t_token **tok, int i)
{
	t_token *token;

	token = *tok;
	if (str[i + 1] == '&')
	{
		token->type = AGGREGATION_IN;
		i++;
	}
	else if (str[i + 1] == '<')
	{
		token->type = HEREDOC;
		i++;
	}
	else
		token->type = REDIR_IN;
	return (i);
}

int				ft_redirection(char *str, t_token **tok, int i, int *redir)
{
	t_token *token;

	token = *tok;
	if (*redir || str[i] == '&')
	{
		*redir = 0;
		return (-1);
	}
	if (str[i] == '>')
		i = ft_redir_o(str, tok, i);
	else if (str[i] == '<')
		i = ft_redir_i(str, tok, i);
	*redir = 1;
	return (i + 1);
}

void			ft_word_type(t_parse **ast, t_token **tok)
{
	t_parse		*current;
	t_token		*token;
	char		*tmp;

	current = *ast;
	token = *tok;
	if (!(current->cmd))
	{
		if (token->value)
			current->cmd = ft_strdup(token->value);
		else
			current->cmd = ft_strnew(1);
	}
	else
	{
		if (token->value)
		{
			tmp = ft_strjoin(current->cmd, " ");
			free(current->cmd);
			tmp[ft_strlen(tmp) - 1] = -1;
			current->cmd = ft_strjoin(tmp, token->value);
			ft_strdel(&tmp);
		}
	}
	*ast = current;
}
