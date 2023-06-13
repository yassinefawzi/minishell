/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/11 02:35:15 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numofarguments(char **args)
{
	int	i;
	int	j;
	int	retval;

	i = 0;
	retval = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][i] == '|')
			{
				retval++;
				while (args[i][j + 1] == '|')
					j++;
			}
			j++;
		}
		i++;
	}
	return (retval + 1);
}

char	**ret_args(char **args)
{
	int		i;
	int		j;
	char	**ret;

	ret = malloc((numofarguments(args) * sizeof(char *)) + 1);
	
	
}

int main(int arc, char **arv, char **enva)
{
	int		i;
	t_env	*envar;
	t_args	*args;
	char	**argums;

	i = 0;
	if (arc > 1)
	{
		envar = ret_env(enva);

		free_list(envar);
	}
}