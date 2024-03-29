/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:35:20 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 05:42:41 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cha;

	i = 0;
	cha = (char )c;
	while (s[i])
	{
		if (s[i] == cha)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cha)
		return ((char *)&s[i]);
	return (NULL);
}
