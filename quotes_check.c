/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:50 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 23:17:16 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_completed(char *str, char cmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == cmp)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	check_single_quote(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = check_if_completed(str + i + 1, str[i]);
			if (j < 0)
				return (-1);
			i += j;
		}
		i++;
	}
	return (0);
}

int	quote_len(char	*str, int i)
{
	int	j;

	j = 0;
	while (str[i + j])
	{
		j++;
		if (str[i + j] == str[i])
			return (j - 1);
	}
	return (-1);
}

int	check_quotes(char *str)
{
	if (check_single_quote(str) < 0)
	{
		error_message("quote error\n");
		return (-1);
	}
	return (0);
}

int	first_quote(char *str, char hol)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != hol)
		i++;
	return (i);
}