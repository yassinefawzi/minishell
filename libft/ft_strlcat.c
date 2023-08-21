/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:09:59 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 23:39:17 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	j;
	size_t	srclen;

	srclen = ft_strlen(src);
	j = 0;
	i = 0;
	if (dst && dst[j])
		j = ft_strlen(dst);
	if (dstsize == 0)
		return (srclen);
	while (src[i] && (i + j) < (dstsize - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	if ((j > dstsize))
		return (srclen + dstsize);
	dst[j + i] = '\0';
	return (srclen + j);
}
