/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:56:44 by oagrram           #+#    #+#             */
/*   Updated: 2019/11/25 22:09:30 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strndup(const char *s, int size)
{
	int			i;
	char		*str;
	char		*src;

	src = (char*)s;
	if (!(str = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (src[i] && i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
