/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:23:34 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 03:52:56 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_error(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	perror(" ");
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
			i = 0;
			while (hol > 0)
			{
				if (tmp->red[1][i] == 1)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_CREAT | O_TRUNC | O_RDWR ,0664);
					if (tmp->fd[i] == -1)
					{
						fd_error(tmp->command[tmp->red[2][i]]);
						tmp->flag_file = -1;
						break;
					}
					tmp->fileout = tmp->fd[i];
				}
				else if (tmp->red[1][i] == 2)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_RDONLY);
					if (tmp->fd[i] == -1)
					{
						fd_error(tmp->command[tmp->red[2][i]]);
						tmp->flag_file = -1;
						break;
					}
					tmp->filein = tmp->fd[i];
				}
				else if (tmp->red[1][i] == 3)
				{
					tmp->fd[i] = open(tmp->command[tmp->red[2][i]], O_CREAT | O_RDWR | O_APPEND, 0644);
					if (tmp->fd[i] == -1)
					{
						fd_error(tmp->command[tmp->red[2][i]]);
						tmp->flag_file = -1;
						break;
					}
					tmp->fileout = tmp->fd[i];
				}
				else if (tmp->red[1][i] == 4)
				{
					tmp->eof = tmp->command[tmp->red[2][i]];
					here_doc(tmp->eof);
					if (tmp->fd[i] == -1)
						fd_error("heredoc");
				}
				i++;
				hol--;
			}
			if (tmp->filein < -1)
				tmp->filein = 0;
			if (tmp->fileout < -1)
				tmp->fileout = 1;
		}
		else
		{
			tmp->filein = 0;
			tmp->fileout = 1;
		}
		tmp = tmp->next;
	}
}

void	close_fd(void)
{
	int		i;
	int		hol;
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
				close(tmp->fd[i]);
				i++;
				hol--;
			}
			free(tmp->fd);
		}
		i = 0;
		tmp = tmp->next;
	}
}