/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:37:23 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/19 17:25:57 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	str = (char *)malloc(i + 1);
	if (!s1)
		return (NULL);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, i + 1);
	return (str);
}
