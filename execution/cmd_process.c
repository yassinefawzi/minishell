/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:31:58 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/21 03:46:40 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*look_for_path(void)
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

void	cmd_proc(char **hol, t_args *tmp, int i)
{
	char	**pathed;
	char	**lst_env;

	lst_env = lst_to_env();
	pathed = ft_split(look_for_path(), ':');
	builtin_proc(tmp);
	i = -1;
	while (pathed[++i])
	{
		pathed[i] = ft_strjoin(pathed[i], "/");
		pathed[i] = ft_strjoin(pathed[i], tmp->command[0]);
	}
	i = -1;
	while (pathed[++i])
		if (access(pathed[i], X_OK) == 0)
			break ;
	if (!pathed[i])
	{
		ft_putstr_fd("Error, path not found.\n", 2);
		exit (2);
	}
	execve(pathed[i], hol, lst_env);
	perror("Error. ");
	free_arr(lst_env);
	free_arr(pathed);
}

void	exec_child_utils(t_args *tmp)
{
	char	**hol;
	int		i;

	hol = malloc((array_len(tmp->command) + 1) * sizeof(char *));
	i = -1;
	while (tmp->command[++i])
	{
		if (tmp->command[i][0] == '>' || tmp->command[i][0] == '<')
			break ;
		hol[i] = ft_strdup(tmp->command[i]);
	}
	hol[i] = 0;
	cmd_proc(hol, tmp, i);
}

void	exec_child(t_args *tmp, int *fd, int flag, int tmp_fd)
{
	if (tmp->flag_file == -1)
		exit(1);
	if (tmp->file > 0)
		dup2(tmp->file, 1);
	else if (tmp->next)
		dup2(fd[1], 1);
	else
		close(fd[1]);
	close(fd[0]);
	if (tmp->filein > 0)
		dup2(tmp->filein, 0);
	else if (flag > 0)
		dup2(tmp_fd, STDIN_FILENO);
	close(fd[0]);
	exec_child_utils(tmp);
	exit(5);
}

void	exe_utils(t_args *tmp, int *fd, int *pids)
{
	int	flag;
	int	tmp_fd;
	int	id;
	int	i;

	i = 0;
	tmp_fd = -1;
	flag = -1;
	while (tmp)
	{
		if (ft_strcmp(tmp->command[0], "cd"))
			i++;
		tmp = tmp->next;
	}
	if (i > 1)
		return ;
	tmp = glo.args;
	if (!ft_strncmp(tmp->command[0], "cd", ft_strlen(tmp->command[0])))
	{
		look_for_old();
		cd(tmp);
		look_for_new();
	}
	if (ft_size_args() > 1)
		pipe(fd);
	id = fork();
	if (id < 0)
	{
		error_message("Error, failed to fork.\n");
		return ;
	}
	pids[++flag] = id;
	if (id == 0)
		exec_child(tmp, fd, flag, tmp_fd);
	
	if (tmp_fd != -1)
		close(tmp_fd);
	close(fd[1]);
	if (tmp->next)
	{
		close(tmp_fd);
		tmp_fd = fd[0];
	}
}
