/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:49:26 by yfawzi            #+#    #+#             */
/*   Updated: 2023/05/20 03:02:12 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *str, char *str1)
{
	int	i;

	if (!str1)
		return (0);
	i = 0;
	while (str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	return (str);
}

int	ft_strcmp(char *str, char *str1)
{
	int	i;

	if (!str || !str1)
		return (0);
	i = 0;
	while (str[i] && str1[i])
	{
		if (str[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}