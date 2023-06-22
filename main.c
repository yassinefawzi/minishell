/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/22 19:52:37 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int	num_of_pipes(char *args)
// {
// 	int	i;
// 	int	ret;

// 	i = 0;
// 	ret = 0;
// 	while (args[i])
// 	{
// 		if (args[i] == '|')
// 		{
// 			if (args[i + 1] == '|')
// 				return ;
			
		
// 		}
// 	}	
// }

// char	**ret_args(char *args)
// {
// 	int		i;
// 	int		j;
// 	char	**ret;

// 	i = 0;
// 	j = 0;
// 	while (args[i])
// 	{
// 		if (args[j] == '|')
// 		{
// 			if (args[j + 1] == '|')
// 				return ;
			
// 		}
		
// 	}
// }

int main(int arc, char **arv, char **enva)
{
	int		i;
	t_env	*envar;
	t_args	*args;
	char	**argums;
	char	*line;
	char	*currdir;

	i = 0;
	while (1)
	{	
		currdir = getcwd(0, 0);
		currdir = ft_strjoin(currdir, " ");
		envar = ret_env(enva);
		line = readline(currdir);
		printf("%s\n", line);
		free(currdir);
		free(line);
		free_list(envar);
	}
}