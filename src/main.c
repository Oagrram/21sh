/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:17:15 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:17:17 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static t_env	*my_getenv(char **env)
{
	int			i;
	t_env		*head;
	t_env		*envp;

	envp = NULL;
	if (!(*env))
		return (envp);
	if (!(head = (t_env *)ft_memalloc(sizeof(t_env))))
		return (envp);
	head->next = NULL;
	envp = head;
	i = 0;
	while (env[i] != NULL)
	{
		envp->data = ft_strdup(env[i]);
		if (!env[i + 1])
			break ;
		if (!(envp->next = (t_env *)ft_memalloc(sizeof(t_env))))
			return (NULL);
		envp = envp->next;
		i++;
	}
	envp->next = NULL;
	return (head);
}

static void		free_env(t_env *envp)
{
	t_env		*curr;
	t_env		*tmp;

	curr = envp;
	while (curr)
	{
		ft_strdel(&curr->data);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}

void			signal_int(int signal)
{
	ft_putstr("\n");
	(void)signal;
}

int				main(int ac, char **av, char **env)
{
	t_env		*envp;

	(void)ac;
	(void)av;
	if (*env)
		envp = my_getenv(env);
	signal(SIGINT, signal_int);
	sh_loop(&envp);
	free_env(envp);
	return (0);
}
