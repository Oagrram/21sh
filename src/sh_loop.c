/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:17:52 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:17:54 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int		sh_loop2(char **line, t_parse **tree, t_env **envp)
{
	int		status;
	char	*tty;
	t_parse	*ast;

	status = 1;
	tty = ttyname(0);
	*tree = ft_parse_tree(line);
	if (line && *line)
		add_to_history(*line, ft_strlen(*line));
	ast = *tree;
	if (*envp)
		if (check_syntax(ast))
			status = sh_execute(&ast, envp, tty);
	return (status);
}

static	void	free_loop(t_parse **ast, char **line)
{
	free_ast(ast);
	ft_strdel(line);
}

void			sh_loop(t_env **envp)
{
	int		status;
	char	*line;
	t_parse	*ast;

	status = 1;
	ast = NULL;
	while (status)
	{
		if ((line = ft_readline("21sh-1.0$ ")))
		{
			if (!ft_strequ("\4", line))
				status = sh_loop2(&line, &ast, envp);
			else
				status = 0;
		}
		free_loop(&ast, &line);
	}
}
