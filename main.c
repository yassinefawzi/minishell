/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/10 08:50:40 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_redirections(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (3);
			return (1);
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (4);
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_for_space_error(char *str)
{
	int		i;
	int		j;
	char	hol;

	if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
	{
		error_message("parsing error\n");
		return (-1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			hol = str[i];
			if (str[i + 2] == hol)
			{
				error_message("parsing error\n");
				return (-1);
			}
			if (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))
			{
				i++;
				while (str[i + 1] == ' ' || str[i + 1] == '\t')
					i++;
				if (str[i + 1] && str[i + 1] == hol)
				{
					error_message("parsing error\n");
					return (-1);
				}
			}
		}
		i++;
	}
	return (1);
}

t_args	*ret_com(char *str)
{
	t_args	*ret_args;
	char	**args;
	int		i;
	int		check_for_double;

	i = 0;
	ret_args = 0;
	if (check_quotes(str) < 0 || check_for_brackets(str) < 0)
		return (0);
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
	while (args[i])
	{
		args[i] = ft_clean(args[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		ft_lstadd_back(&ret_args, ft_lstnew_args(args[i]));
		ret_args->red = check_for_redirections(args[i]);
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
		{
			printf("%s\n", args->command[i]);
			i++;
		}
		printf("%d\n", args->red);
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