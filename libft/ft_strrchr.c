/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:30 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/23 22:49:00 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cha;

	cha = (char )c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == cha)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
