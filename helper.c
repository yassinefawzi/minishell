/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:49:26 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/12 07:32:52 by yfawzi           ###   ########.fr       */
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
					str[i] = 2;
				else if (str[i] == '<')
					str[i] = 3;
				i++;
			}
			i++;
		}
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
		i++;
	}
}

void	ret_index(t_args *args)
{
	t_args	*tmp;
	char	*str;
	int		i;

	if (!args)
		return ;
	i = 0;
	tmp = args;
	while (tmp)
	{
 		if (tmp->red > 0)
		{
			if (tmp->red == 1 || tmp->red == 3)
			{
				while (tmp->command[i][0] != '>')
					i++;
				tmp->red_index = i + 1;
				i = 0;		
			}
			else if (tmp->red == 2 || tmp->red == 4)
			{
				while (tmp->command[i][0] != '<')
					i++;
				tmp->red_index = i + 1;
				i = 0;
			}
		}
		tmp = tmp->next;
	}
}