/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:45:31 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/29 22:48:43 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_digit(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	printf_message(char *cmd)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 18);
	ft_putstr_fd(cmd, 2);
	write(2, ": numeric argument required\n", 29);
	exit(255);
}

long	str_to_uint(char *str)
{
	long	pre;
	long	result;
	int		i;
	int		sign;

	i = -1;
	pre = 0;
	sign = 1;
	result = 0;
	while (str[++i])
	{
		if ((str[i] == '+' || str[i] == '-') && i == 0)
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		if (!check_digit(str[i]))
			printf_message(str);
		result = result * 10 + (str[i] - '0');
		if (pre > result)
			printf_message(str);
		pre = result;
	}
	return (sign * result);
}

void	re_exit(char **cmd)
{
	long	num;

	if (!cmd[1])
		exit(glo.exit_status);
	num = str_to_uint(cmd[1]);
	if (cmd[2])
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 37);
		glo.exit_status = 1;
		return ;
	}
	else if (cmd[1])
	{
		write(1, "exit\n", 5);
		glo.exit_status = (unsigned int)num;
	}
	exit(glo.exit_status);
}
