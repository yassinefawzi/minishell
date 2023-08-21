/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:30:59 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/20 21:34:40 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_child(char *eof, int *fd)
{
	char	*lexer;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		lexer = readline("herecod> ");
		if (!eof || ft_strcmp(lexer, eof) > 0)
		{
			free(lexer);
			break ;
		}
		write(fd[1], lexer, ft_strlen(lexer));
		write(fd[1], "\n", 1);
		free(lexer);
	}
	close (fd[1]);
	exit (0);
}

void	here_doc(char *eof)
{
	int	fd[2];
	int	pid;
	int	count;

	count = 0;
	if (eof)
	{
		while (1)
		{
			count++;
			if (count > 16)
				return ;
			pipe(fd);
			pid = fork();
			if (pid == 0)
				execute_child(eof, fd);
			else
			{
				close (fd[1]);
				wait(NULL);
				return ;
			}
		}
	}
}
