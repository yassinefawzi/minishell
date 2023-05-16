/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 01:18:13 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/23 23:24:23 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	if (dest == NULL && src == NULL)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	while (n)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}
