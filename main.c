/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 09:29:28 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glo	glo;

t_args	*ret_com(char *str)
{
	t_args	*ret_args;
	t_args	*tmp;
	char	**args;
	int		i;
	int		check_for_double;

	ret_args = 0;
	if (check_quotes(str) < 0 || check_for_brackets(str) < 0)
	{
		free(str);
		return (0);
	}
	hidden_symbols(str);
	str = cleaned_spaces(str, 0, 0, 0);
	if (check_for_space_error(str) < 0)
	{
		free(str);
		return (0);
	}
	if (check_for_pipes(str) < 0 || check_for_empty_pipe(str) < 0)
	{
		free(str);
		return (0);
	}
	check_for_double = check_if_valid(str);
	if (check_for_double >=  0)
	{
		if (check_for_double == 0)
		{
			free(str);
			return (NULL); 
		}
		str = fixed_pipes(str, check_for_double);
	}
	args = ft_split(str, '|');
	i = 0;
	while (args[i])
	{
		args[i] = ft_clean(args[i], 0, 0);
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
		{
			return_symbol(tmp->command[i]);
			tmp->command[i] = check_var(tmp->command[i], 0, 0, 0);
			i++;
		}
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
		i = 0;
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

void	hadnle_signle(int n)
{
	(void) n;
	write(1, "\n", 1);
	rl_replace_line ("", 0);
	rl_on_new_line();
	rl_redisplay();
	glo.exit_status = 1;
}

int main(int arc, char **arv, char **enva)
{
	t_env	*envar;
	t_args	*args;
	char	*line;
	(void)arc;
	(void)arv;
	envar = ret_env(enva);
	glo.env = envar;
	while (1)
	{
		signal (SIGINT, hadnle_signle);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(line);  
		args = ret_com(line);
		glo.args = args;
		ret_fd();
		final_cmd();
		execution();
		// ft_printer(glo.args);
		close_fd();
		ft_free(args);
	}
	free_list(envar);
}