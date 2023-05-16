/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:02:51 by yfawzi            #+#    #+#             */
/*   Updated: 2022/11/09 17:40:04 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	num;
	int						sign;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == ' ')
		|| (str[i] == '\r') || (str[i] == '\v') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + str[i++] - 48;
	if (num > 9223372036854775807 && sign == -1)
		return (0);
	else if (num > 9223372036854775807 && sign == 1)
		return (-1);
	return (num * sign);
}
