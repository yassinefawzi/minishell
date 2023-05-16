/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:24:16 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/23 23:30:30 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*st;
	int				i;

	i = 0;
	st = (unsigned char *)s;
	ch = (unsigned char )c;
	while (n--)
	{
		if (st[i] == ch)
			return ((void *)s + i);
		else
			i++;
	}
	return (NULL);
}
