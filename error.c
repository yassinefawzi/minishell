/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:48:06 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 23:16:48 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
}

int	check_for_space_error(char *str)
{
	int		i;
	char	hol;

	i = 0;
	if (str[i])
	{
		if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
		{
			error_message("parsing error\n");
			return (-1);
		}
		i = 0;
		while (str[i])
		{
			if (str[i] == '>')
				if (str[i + 1] == '<')
				{
					error_message("parsing error\n");
					return (-1);
				}
			i++;
		}
		i = 0;
		while (str[i])
		{
			if (str[i] == '>' || str[i] == '<')
			{
				hol = str[i];
				if ((str[i + 1] == ' ' && str[i + 2] == hol))
				{
					error_message("parsing error\n");
					return (-1);
				}
				if (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))
				{
					i++;
					while (str[i + 1] == ' ' || str[i + 1] == '\t')
						i++;
					if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
					{
						error_message("parsing error\n");
						return (-1);
					}
				}
			}
			i++;
		}
	}
	return (1);
}