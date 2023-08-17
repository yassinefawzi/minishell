/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:23:34 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/17 21:07:39 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_error(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	perror(":\n");
}

void	ret_fd(void)
{
	int		i;
	t_args	*tmp;
	int		hol;

	i = 0;
	tmp = glo.args;
	while (tmp)
	{
		hol = tmp->red[0][0];
		if (hol > 0)
		{
			tmp->fd = malloc(hol * 4);
			while (hol > 0)
			{
				if (tmp->red[1][i] == 1)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_CREAT ,0664);
					if (tmp->fd[i] == -1)
						fd_error(tmp->command[tmp->red[2][i]]);
				}
				if (tmp->red[1][i] == 2)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_RDONLY);
					if (tmp->fd[i] == -1)
						fd_error(tmp->command[tmp->red[2][i]]);
				}
				if (tmp->red[1][i] == 3)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_CREAT | O_WRONLY | O_APPEND, 0644);
					if (tmp->fd[i] == -1)
						fd_error(tmp->command[tmp->red[2][i]]);
				}
				if (tmp->red[1][i] == 4)
				{
					tmp->fd[i] = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0664);
					if (tmp->fd[i] == -1)
						fd_error("heredoc");
				}
				i++;
				hol--;
			}
		}
		else
			tmp->file = -1;
		i = 0;
		if (tmp->red[0][0] > 0)
			tmp->file = tmp->fd[tmp->red[0][0] - 1];
		else
			tmp->file = -1;
		tmp = tmp->next;
	}
}

void	close_fd(void)
{
	int		i;
	int		hol;
	int j = 1;
	t_args	*tmp;

	i = 0;
	tmp = glo.args;
	while (tmp)
	{
		hol = tmp->red[0][0];
		if (hol > 0)
		{
			while (hol > 0)
			{
				j = close(tmp->fd[i]);

				i++;
				hol--;
			}
			free(tmp->fd);
		}
		i = 0;
		tmp = tmp->next;
	}
}