/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:35:52 by yoelansa          #+#    #+#             */
/*   Updated: 2023/08/20 22:56:12 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**lst_to_env(void)
{
	t_env	*tmp;
	char	**ret;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	tmp = glo.env;
	ret = malloc((ft_size_env() + 1) * sizeof(char *));
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

void	free_and_close(int	*pids, int *save_fds)
{
	if (ft_size_args() > 0)
		free(pids);
	dup2(save_fds[0], 0);
	close(save_fds[0]);
	dup2(save_fds[1], 1);
	close(save_fds[1]);
}
