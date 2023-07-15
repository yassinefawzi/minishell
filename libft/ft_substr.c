/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:05:34 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/15 04:26:46 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s) + 1)
		return (ft_calloc(1, 1));
	i = 0;
	while (s[i + start] && i < len)
		i++;
	s1 = (char *)malloc((i + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}
