/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:15:18 by oagrram           #+#    #+#             */
/*   Updated: 2021/03/25 15:15:23 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		ft_redir_inout(t_redirection *redirect, int fd)
{
	int		left;

	if (redirect->type == REDIR_OUT)
		fd = open(redirect->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		fd = open(redirect->right, O_RDONLY);
		if (fd < 0)
			return (redirect_error(redirect));
	}
	if (redirect->left)
	{
		left = ft_atoi(redirect->left);
		dup2(fd, left);
	}
	else
	{
		if (redirect->type == REDIR_OUT)
			dup2(fd, 1);
		else
			dup2(fd, 0);
	}
	close(fd);
	return (255);
}

int		ft_redir_append(t_redirection *redir, int fd)
{
	int		left;

	fd = open(redir->right, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->left)
	{
		left = ft_atoi(redir->left);
		dup2(fd, left);
	}
	else
		dup2(fd, 1);
	close(fd);
	return (fd);
}

int		ft_agg_digit(t_redirection *redir, int fd, int left)
{
	fd = ft_atoi(redir->right);
	if (fd != left)
	{
		if (dup2(fd, left) < 0)
		{
			ft_putstr_fd("21sh: ", 2);
			ft_putnbr_fd(fd, 2);
			ft_putendl_fd(": Bad file descriptor\n", 2);
			return (-1);
		}
	}
	return (fd);
}

int		ft_agg_word(t_redirection *redir, int fd, int left)
{
	fd = open(redir->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != left)
	{
		dup2(fd, left);
		if (!redir->left)
			dup2(fd, 2);
	}
	close(fd);
	return (fd);
}
