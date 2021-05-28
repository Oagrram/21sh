/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 02:04:56 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/09/16 18:36:53 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_die(const char *message, int error_nb)
{
	if (error_nb != 0 && message)
		ft_putendl_fd(message, 2);
	else if (message)
		ft_putstr(message);
	exit(error_nb);
}
