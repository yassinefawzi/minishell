/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:15:05 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 05:18:29 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **command)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	j = 1;
	k = 0;
	if (!command[1])
	{
		printf("\n");
		return	;
	}
	while (command[i])
	{
		if (command[i][0] == '-')
		{
			while (command[i][j] == 'n')
				j++;
			if (command[i][j] != 'n' && command[i][j] != '\0')
				break ;
			k = 1;
		}
		if (command[i][0] != '-')
			break ;
		j = 0;
		i++;
	}
	if (k == 0)
		i = 1;
	if (command[i])
	{
		if (k > 0)
		{
			while (command[i])
			{
				if (command[i + 1])
					printf("%s ", command[i++]);
				else
					printf("%s", command[i++]);
			}
		}
		else
		{
			while (command[i])
			{
				if (command[i + 1])
					printf("%s ", command[i++]);
				else
					printf("%s", command[i++]);
			}
			printf("\n");
		}
	}
}

t_env	*look_for_pwd(void)
{
	t_env	*tmp;

	tmp = glo.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD=") > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	look_for_old(void)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = glo.env;
	tmp1 = glo.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD=") > 0)
		{
			free(tmp->value);
			tmp1 = look_for_pwd();
			tmp->value = ft_strdup(tmp1->value);
		}
		tmp = tmp->next;
	}
}

void	look_for_new(void)
{
	t_env	*tmp;

	tmp = glo.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD=") > 0)
		{
			free(tmp->value);
			tmp->value = 0;
			break ;
		}
		tmp = tmp->next;
	}
}
void	cd(char **command)
{
	int		val;
	char	*str;
	char	*str1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!command[1])
		return ;
	val = chdir(command[1]);
	if (val < 0)
	{
		str = getcwd(0, 0);
		i = ft_strlen(str);
		j = ft_strlen(command[1]);
		str1 = malloc(i + j + 1);
		str1 = ft_strcpy(str1, str);
		str1[i] = '/';
		str1[i + 1] = '\0';
		str1 = ft_strjoin(str1, command[1]);
		val = chdir(str1);
		free(str1);
		if (val < 0)
			perror("cd");
		free(str);
	}
}

void	pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	printf("%s\n", str);
	free(str);
}

void	env(void)
{
	t_env	*tmp;

	tmp = glo.env;
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}


int	check_for_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (-1);
}

void	add_new_var(char *str0, char *str1)
{
	t_env	*last;
	t_env	*new_elem;

	new_elem = malloc(sizeof(t_env));
	last = glo.env;
	while (last->next)
	{
		last = last->next;
	}
	new_elem->name = ft_strdup(str0);
	if (!str1)
		new_elem->value = ft_strdup("\n");
	else
		new_elem->value = ft_strdup(str1);
	new_elem->next = NULL;
	last->next = new_elem;
}

void	export(char *str)
{
	t_env	*tmp;
	t_env	*ret;
	char	**hol;
	int		i;

	i = 2;
	tmp = glo.env;
	if (!str)
	{
		while (tmp)
		{
			printf("declare -x ");
			printf("%s", tmp->name);
			printf("%s\n", tmp->value);
			tmp = tmp->next;
		}
		return ;
	}
	hol = ft_split(str, '=');
	if (hol[1])
	{
		while(hol[i])
		{
			hol[1] = ft_strjoin(hol[1], "=");
			hol[1] = ft_strjoin(hol[1], hol[i++]);
		}
	}
	hol[0] = ft_strjoin(hol[0], "=");
	i = 0;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strlen(tmp->name) == ft_strlen(hol[0]))
			{
				if (ft_strncmp(tmp->name, hol[0], ft_strlen(hol[0])) == 0)
				{
					i = 1;
					break ;
				}
			}
			tmp = tmp->next;
		}
		if (tmp)
		{
			if (ft_strlen(tmp->name) == ft_strlen(hol[0]))
			{
				if (ft_strncmp(tmp->name, hol[0], ft_strlen(hol[0])) == 0)
					i = 1;
			}
		}
		if (i == 1)
		{
			free(tmp->value);
			tmp->value = ft_substr(hol[1], 0, ft_strlen(hol[1]));
			i = 0;
			while (hol[i])
				free(hol[i++]);
			free(hol);
			return ;
		}
	}
	ret = malloc(sizeof(t_env));
	ret->name = ft_strdup(hol[0]);
	ret->value = ft_strdup(hol[1]);
	ret->next = 0;
	if (glo.env)
		glo.env = ret;
	else
		tmp->next = ret;
	i = 0;
	while (hol[i])
		free(hol[i++]);
	free(hol);
}
