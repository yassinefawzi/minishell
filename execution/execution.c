/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:19:43 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 22:52:08 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_args *tmp)
{
	int		i;
	int		fd[2];
	int		save_fds[2];
	int		*pids;
	int		status;

	save_fds[0] = dup(STDIN_FILENO);
	save_fds[1] = dup(STDOUT_FILENO);
	pids = malloc(sizeof(int) * ft_size_args());
	while (tmp)
	{
		exe_utils(tmp, fd, pids);
		tmp = tmp->next;
	}
	i = -1;
	while (++i < ft_size_args())
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		glo.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		glo.exit_status = 128 + WTERMSIG(status);
	free_and_close(pids, save_fds);
}
