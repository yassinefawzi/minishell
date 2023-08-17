/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:30:59 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/18 00:35:27 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/readline/readline.h"
#include "/usr/include/readline/history.h"
// #include <readline/history.h>

// char    *remove_spaces(char *lexer)
// {
//     char    *str;
//     int        i;

//     i = 0;
//     while (lexer[i] && lexer[i] != ' ')
//         i++;
//     str = malloc(i + 1);
//     if (!str)
//         return (0);
//     i = 0;
//     while (lexer[i] && lexer[i] != ' ')
//     {
//         str[i] = lexer[i];
//         i++;
//     }
//     str [i] = '\0';
//     return (str);
// }

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}
int	ft_strcmp(char *str, char *str1)
{
	int	i;

	if (!str || !str1)
		return (0);
	i = 0;
	while (str[i] && str1[i])
	{
		if (str[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}

void    here_doc(char *s)
{
    char    *str; //fot delemetre
    int     fd[2];
    int     pid;
    int     count = 0;
    if (s)
    {
        while(1)
        {
            count++;
            if (count > 16)
                exit(2);
            pipe(fd);
            pid = fork();
            if (pid == 0)
            {
                close(fd[0]);
                while (1)
                {
                    str = readline("herecod> ");
                    if (!str)
                        break ;
                    else if (!ft_strcmp(str, s))
                    {
                        free(str);
                        break ;
                    }
                    write(fd[1], str, ft_strlen(str));
                    write(fd[1], "\n", 1);
                    free(str);
                }
                close (fd[1]);
                exit (0);
            }
            else
            {
                close (fd[1]);
                wait(NULL);
                // tmp->fd = fd[0];
                // char c;
                // printf("\n str \n");
                // while (read(fd[0], &c, 1))
                //     write(1, &c, 1);
            }
        }
    }
}
int main(int ac, char **av)
{
    if (ac == 2)
    {
        here_doc(av[1]);
    }
}











































// void	handle_child_process(int fd[2], t_file *tmp, int flag)
// {
// 	char	*str;

// 	signal(SIGINT, SIG_DFL);
// 	close(fd[0]);
// 	str = read_and_write(flag, tmp->filename, fd);
// 	close(fd[1]);
// 	exit(0);
// }

// int	handle_parent_process(int fd[2], int pid, t_file *tmp)
// {
// 	close(fd[1]);
// 	wait(&pid);
// 	tmp->fd = fd[0];
// 	if (WIFSIGNALED(pid))
// 		return (3);
// 	return (0);
// }

// int	handle_file(t_data *lexer, int fd[2])
// {
// 	t_file	*tmp;
// 	int		pid;
// 	int		flag;

// 	tmp = lexer->file;
// 	while (tmp)
// 	{
// 		if (tmp->type == 4)
// 		{
// 			flag = check_flag(tmp);
// 			pipe(fd);
// 			pid = fork();
// 			if (pid == 0)
// 				handle_child_process(fd, tmp, flag);
// 			else
// 			{
// 				if (handle_parent_process(fd, pid, tmp) == 3)
// 					return (3);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	iterate_files(t_data *lexer, int fd[2])
// {
// 	while (lexer)
// 	{
// 		if (handle_file(lexer, fd) == 3)
// 			return (3);
// 		lexer = lexer->next;
// 	}
// 	return (0);
// }

// int	here_document(t_data *lexer)
// {
// 	int	fd[2];

// 	return (iterate_files(lexer, fd));
// }