/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/20 12:41:56 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	signal_resize(int sig)
{
	struct winsize	wn;

	(void)sig;
	ioctl(1, TIOCGWINSZ, &wn);
	g_readline->col = wn.ws_col;
	g_readline->row = wn.ws_row;
}

void	signal_c(int sig)
{
	(void)sig;
	g_readline->config.c_cc[VMIN] = 0;
	if (tcsetattr(0, 0, &g_readline->config) < 0)
		ft_die("Can't set terminal config", -11);
}
