/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:19:43 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/17 21:22:51 by yfawzi           ###   ########.fr       */
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
int		array_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void    execution(void)
{
    t_args  *tmp;
    int     i;
    int     id;
    int     fd[2];
	int		tmp_fd;
	int save_fds[2];
	char	**pathed;
	char **lst_env = lst_to_env();
	char	**hol;

	save_fds[0] = dup(STDIN_FILENO);
	save_fds[1] = dup(STDOUT_FILENO);
	hol = 0;
	pathed = ft_split(look_for_path(), ':');
	i = 0;
    tmp = glo.args;
	tmp_fd = -1;
	int flag = 0;
	int *pids = malloc(sizeof(int) * ft_size_args());
    while (tmp)
    {
		if (tmp->next)
        	pipe(fd);
        id = fork();
		if (id < 0)
		{
			error_message("Error, failed to fork.\n");
			return ;
		}
		pids[flag] = id;
		if (id == 0)
		{	
			if (tmp->next)
			{
				close(fd[0]);
				if (tmp->red[0][0] > 0 && (tmp->red[1][tmp->red[0][0] - 1] == 1 || tmp->red[1][tmp->red[0][0] - 1] == 3))
					dup2(tmp->file, STDOUT_FILENO);
				else
					dup2(fd[1], STDOUT_FILENO);
			}
			else if (tmp->red[0][0] > 0)
			{
				if (tmp->red[0][0] > 0 && (tmp->red[1][tmp->red[0][0] - 1] == 1 || tmp->red[1][tmp->red[0][0] - 1] == 3))
				{
					dup2(tmp->file, STDOUT_FILENO);
				}
			}
			else
				close(fd[1]);
			if (flag > 0)	
			{
				if (tmp->red[0][0] > 0 && (tmp->red[1][tmp->red[0][0] - 1] == 2 || tmp->red[1][tmp->red[0][0] - 1] == 4))
					dup2(tmp_fd, tmp->file);
				else
					dup2(tmp_fd, STDIN_FILENO);
			}
			close(fd[0]);
			hol = malloc((array_len(tmp->command) + 1) * sizeof(char *));
			while (tmp->command[i])
			{
				if (tmp->command[i][0] == '>' || tmp->command[i][0] == '<')
					break ;
				hol[i] = ft_strdup(tmp->command[i]);
				i++;
			}
			hol[i] = 0;
			i = 0;
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
			execve(pathed[i], hol, lst_env);
			perror("Error. ");
			exit(5);
		}
		i = 0;
		if (tmp_fd != -1)
			close(tmp_fd);
		if (ft_size_args() > 1)
		{
			close(fd[1]);
			close(tmp_fd);
			tmp_fd = fd[0];
		}
		flag++;
		tmp = tmp->next;
	}
	i = 0;
	while (i < ft_size_args())
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	if (ft_size_args() > 0)
		free(pids);
	dup2(save_fds[0], 0);
	close(save_fds[0]);
	dup2(save_fds[1], 1);
	close(save_fds[1]);
	i = 0;
	while (lst_env[i])
		free(lst_env[i++]);
	i = 0;
	while (pathed[i])
		free(pathed[i++]);
	i = 0;
	free(pathed);
	free(lst_env);	
}