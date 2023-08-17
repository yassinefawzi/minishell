/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:19:43 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/17 03:18:58 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char *look_for_path(void)
{
    t_env	*tmp;

	tmp = glo.env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, "PATH="))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
int	ft_size_env(void)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = glo.env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_size_args(void)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = glo.args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char **lst_to_env(void)
{
	t_env	*tmp;
	char	**ret;
	int		i;

	i = 0;
	char *key, *value;
	tmp = glo.env;
	ret = malloc((ft_size_env() + 1 )* sizeof(char *));
	while (tmp)
	{
		key = ft_strdup(tmp->name);
		value = ft_strdup(tmp->value);
		ret[i] = ft_strjoin(key, value);
		free(value);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	i = 0;
	return (ret);	
}

void    execution(void)
{
    t_args  *tmp;
    int     i;
    int     id;
    int     fd[2];
	int		tmp_fd;
	char	**pathed;
	char **lst_env = lst_to_env();

	pathed = ft_split(look_for_path(), ':');
	i = 0;
    tmp = glo.args;
	tmp_fd = -1;
	int flag = 0;
	int *pids = malloc(sizeof(int) * ft_size_args());
    while (tmp)
    {
		if (flag > 0)
		{
			printf("pipe\n");
        	pipe(fd);
		}
        id = fork();
		if (id < 0)
		{
			error_message("Error, failed to fork.\n");
			return ;
		}
		pids[flag] = id;
		if (id == 0)
		{	
			// check if there is infiles and outfiles
			if (tmp->next != NULL)
				dup2(fd[1], 1);
			else
				close(fd[1]);
			if (flag > 0)
				dup2(tmp_fd, 0);
			close(fd[0]);
			while(pathed[i])
			{
				pathed[i] = ft_strjoin(pathed[i], "/");
				pathed[i] = ft_strjoin(pathed[i], tmp->command[0]);
				i++;
			}
			i = 0;
			while (pathed[i])
			{
				if (access(pathed[i], X_OK) == 0)
					break ;
				i++;
			}
			if (!pathed[i])
			{
				ft_putstr_fd("Error, path not found.\n", 2);
				exit (2);
			}
			if (tmp->command[1] && tmp->command[1][0] == '-')
			{
				pathed[i] = ft_strjoin(pathed[i], " ");
				pathed[i] = ft_strjoin(pathed[i], tmp->command[1]);
			}
			execve(pathed[i], &tmp->command[0], lst_env);
			perror("Error. ");
			exit(5);
		}
	// 	printf("tmp fd inside the while: %d\n", tmp_fd);
	// 	if (tmp_fd != -1)
	// 	{
	// 		printf("tmp fddddddd : %d\n", tmp_fd);
	// 		close(tmp_fd);
	//	}
		if (ft_size_args() > 1)
		{
			close(tmp_fd);
			tmp_fd = fd[0];
			close(fd[1]);
		}
		flag++;
		tmp = tmp->next;
	}
	// printf("tmp fd : %d\n", tmp_fd);
	i = 0;
	while (i < ft_size_args())
	{
		printf("waiting child : %d\n", pids[i]);
		waitpid(pids[i], NULL, 0);
		i++;
	}
}