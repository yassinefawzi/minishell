/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:56:34 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 08:58:31 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_pipes(char *str, int num)
{
	int	i;

	i = 0;
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		i++;
	}
	return (i);
}

char	*fixed_pipes(char *str, int num)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(len_of_pipes(str, num) + 1);
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	free(str);
	return (ret);
}

int	check_for_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '|')
			return (error_message("parse error near `|'\n"));
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (error_message("parse error near `|'\n"));
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] == '\0' || str[i] == '|')
				return (error_message("parse error near `|'\n"));
		}
		if (str[i])
			i++;
	}
	return (1);
}

int	check_for_empty_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (!str[i + 1])
			{
				error_message("pipe error\n");
				return (-1);
			}
		}
		i++;
	}
	return (1);
}