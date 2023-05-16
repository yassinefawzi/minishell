/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:51:40 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/22 03:11:12 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	comptable(long int *n1)
{
	int			i;
	long int	n2;

	i = 0;
	n2 = *n1;
	if (n2 < 0)
	{
		i++;
		*n1 *= -1;
		n2 *= -1;
	}
	while (n2 > 9)
	{
		i++;
		n2 /= 10;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	long int	n1;
	char		*str;
	int			len;

	n1 = (long int )n;
	len = comptable(&n1);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len - 1 >= 0)
	{
		str[len - 1] = (n1 % 10) + 48;
		n1 /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
