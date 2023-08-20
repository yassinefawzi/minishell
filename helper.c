/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:49:26 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 20:05:09 by yfawzi           ###   ########.fr       */
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

void	hidden_symbols(char *str)
{
	int		i;
	char	hol;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			hol = str[i++];
			while (str[i] && str[i] != hol)
			{
				if (str[i] == '|')
					str[i] = 1;
				else if (str[i] == '>')
				{
					if (str[i - 1] != hol && str[i + 1] != hol)
						str[i] = 2;
				}
				else if (str[i] == '<')
				{
					if (str[i - 1] != hol && str[i + 1] != hol)
						str[i] = 3;
				}	
				else if (str[i] == '$')
					str[i] = 4;
				i++;
			}
			if (str[i])
				i++;
		}
		if (str[i])
			i++;
	}
}

void	return_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = '|';
		else if (str[i] == 2)
			str[i] = '>';
		else if (str[i] == 3)
			str[i] = '<';
		else if (str[i] == 4)
			str[i] = '$';
		i++;
	}
}
