/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/13 12:52:13 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ret_com(char *str)
{
	t_args	*ret_args;
	t_args	*tmp;
	char	**args;
	int		i;
	int		check_for_double;

	ret_args = 0;
	if (check_quotes(str) < 0 || check_for_brackets(str) < 0)
		return (0);
	hidden_symbols(str);
	str = cleaned_spaces(str);
	if (check_for_space_error(str) < 0)
		return (0);
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
	i = 0;
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
	ret_red(ret_args);
	tmp = ret_args;
	while (tmp)
	{
		i  = 0;
		while (tmp->command[i])
			return_symbol(tmp->command[i++]);
		tmp = tmp->next;
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(str);
	return (ret_args);
}

void	ft_printer(t_args *arg)
{
	int		i;
	int		hol;
	t_args	*args;

	i = 0;
	args = arg;
	while (args)
	{
		while (args->command[i])
			printf("%s\n", args->command[i++]);
		i = 0;
		printf("num of red == %d\n", args->red[0][0]);
		hol = args->red[0][0];
		while (i < hol)
		{
			printf("red[%d] index == %d is: %d\n", i, args->red[2][i], args->red[1][i]);
			i++;
		}
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
		glo.args = args;
		glo.env = envar;
		ft_printer(args);
		free(currdir);
		ft_free(args);
		free_list(envar);
	}

}