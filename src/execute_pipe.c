/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:14:38 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:14:40 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	void			execute_pipe2(t_parse *ast, t_pipe_variable **var)
{
	t_parse			*current;
	t_pipe_variable	*variable;

	current = ast;
	variable = *var;
	close(variable->pip[0]);
	if (variable->cmd_nbr != 0)
	{
		dup2(variable->tmp, 0);
		close(variable->tmp);
	}
	if (current->pipe)
		dup2(variable->pip[1], 1);
	close(variable->pip[1]);
	if (current->redirection)
		execute_redirection(current->redirection, variable->tty);
}

static	t_pipe_variable	*execute_pipe1(t_parse *ast, t_pipe_variable **var,
										char **tabs, t_env **envp)
{
	t_parse			*current;
	t_pipe_variable *variable;

	current = ast;
	variable = *var;
	if (pipe(variable->pip) == -1)
		return (NULL);
	variable->pid = fork();
	if (variable->pid == 0)
	{
		execute_pipe2(current, &variable);
		execute_simple_cmd(current->cmd, tabs, envp);
		exit(0);
	}
	close(variable->pip[1]);
	if (variable->cmd_nbr != 0)
		close(variable->tmp);
	variable->tmp = variable->pip[0];
	variable->cmd_nbr++;
	return (variable);
}

int						execute_pipe(t_parse *ast, t_env **envp, char **tabs,
									char *tty)
{
	t_pipe_variable	*variable;
	t_parse			*current;

	current = ast;
	if (!(variable = (t_pipe_variable*)ft_memalloc(sizeof(t_pipe_variable))))
		return (-1);
	variable->cmd_nbr = 0;
	variable->tmp = 0;
	variable->tty = tty;
	while (current)
	{
		variable = execute_pipe1(current, &variable, tabs, envp);
		current = current->pipe;
	}
	close(variable->tmp);
	if (variable->pid)
		while (wait(NULL) > 0)
		{
		}
	free(variable);
	return (255);
}
