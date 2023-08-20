/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:47:46 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/19 01:55:31 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (s == NULL)
		return (NULL);
	j = 0;
	while (s1 && s1[j])
	{
		s[j] = s1[j];
		j++;
	}
	if (s1)
		free(s1);
	i = 0;
	while (s2 && s2[i])
	{
		s[j + i] = s2[i];
		i++;
	}
	//if (s2)
		//free((char *)s2);
	s[j + i] = '\0';
	return (s);
}
