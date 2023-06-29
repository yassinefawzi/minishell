/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:08:55 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/29 00:59:18 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_command(char *str)
{
	char	*ret;
	int		i;

	ret = malloc(ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		ret = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
