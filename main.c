/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/08 00:56:59 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ret_com(char *str)
{
	t_args	*ret_args;
	char	**args;
	int		i;
	int		check_for_double;

	i = 0;
	ret_args = 0;
	if (check_quotes(str) < 0)
		return (0);
	str = cleaned_spaces(str);
	if (check_for_pipes(str) < 0 || check_for_empty_pipe(str) < 0)
		return (0);
	check_for_double = check_if_valid(str);
	if (check_for_double >=  0)
	{
		if (check_for_double == 0)
			return (NULL); 
		str = fixed_pipes(str, check_for_double);
	}
	args = ft_split(str, '|');
	while (args[i])
	{
		args[i] = ft_clean(args[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		ft_lstadd_back(&ret_args, ft_lstnew_args(args[i]));
		i++;
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (ret_args);
}

void	ft_printer(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		while (args->command[i])
			printf("%s\n", args->command[i++]);
		i = 0;
		printf("-------------\n");
		args = args->next;
	}
}

int main(int arc, char **arv, char **enva)
{
	int		i;
	t_env	*envar;
	t_args	*args;
	char	*line;
	char	*currdir;

	i = 0;
	while (1)
	{	
		currdir = getcwd(0, 0);
		currdir = ft_strjoin(currdir, " ");
		envar = ret_env(enva);
		line = readline(currdir);
		add_history(line);  
		args = ret_com(line);
		ft_printer(args);
		free(currdir);
		ft_free(args);
		free_list(envar);
	}

} 