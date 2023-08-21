/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:23:28 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/21 03:17:20 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") > 0)
		return (1);
	else if (ft_strcmp(cmd, "env") > 0)
		return (2);
	else if (ft_strcmp(cmd, "pwd") > 0)
		return (3);
	else if (ft_strcmp(cmd, "cd") > 0)
		return (4);
	else if (ft_strcmp(cmd, "exit") > 0)
		return (5);
	else if (ft_strcmp(cmd, "export") > 0)
		return (6);
	else if (ft_strcmp(cmd, "unset") > 0)
		return (7);
	return (0);
}

void	exec_builtin(t_args *args)
{
	int	is_b;

	is_b = is_builtin(args->command[0]);
	if (is_b == 1)
		echo(args);
	else if (is_b == 2)
		env();
	else if (is_b == 3)
		pwd();
	else if (is_b == 5)
		ft_exit();
	else if (is_b == 6)
		export(args->command[0]);
	else if (is_b == 7)
		ft_unset(args->command);
	exit (5);
}

void	builtin_proc(t_args *args)
{
	if (is_builtin(args->command[0]))
		exec_builtin(args);
	return ;
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}
