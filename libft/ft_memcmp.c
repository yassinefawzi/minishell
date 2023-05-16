/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:49:56 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/23 23:28:37 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			j;

	j = 0;
	while (j < n)
	{
		if (*(unsigned char *)(s1 + j) == *(unsigned char *)(s2 + j))
			j++;
		else
			return (*(unsigned char *)(s1 + j) - *(unsigned char *)(s2 + j));
	}
	return (0);
}
