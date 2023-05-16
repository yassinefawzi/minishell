/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:07:31 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/24 05:04:30 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (haystack == NULL && needle && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && needle[j] && len)
	{
		while (haystack[i + j] == needle[j] && len)
		{
			len--;
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		len += j;
		j = 0;
		len--;
		i++;
	}
	return (NULL);
}
