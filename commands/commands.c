/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:15:05 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 22:56:22 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(t_args *args)
{
	int		i;
	int		j;
	int		k;
	t_args	*tmp;

	tmp = args;
	i = 1;
	j = 1;
	k = 0;
	while (tmp->command[i])
	{
		if (tmp->command[i][0] == '-')
		{
			while (tmp->command[i][j] == 'n')
				j++;
			if (tmp->command[i][j] != 'n' && tmp->command[i][j] != '\0')
				break ;
			k = 1;
		}
		if (tmp->command[i][0] != '-')
			break ;
		j = 0;
		i++;
	}
	if (k == 0)
		i = 1;
	if (tmp->command[i] && tmp->red[0][0] == 0)
	{
		if (k > 0)
		{
			while (tmp->command[i])
			{
				if (tmp->command[i + 1])
					printf("%s ", tmp->command[i++]);
				else
					printf("%s", tmp->command[i++]);
			}
		}
		else
		{
			while (tmp->command[i])
			{
				if (tmp->command[i + 1])
					printf("%s ", tmp->command[i++]);
				else
					printf("%s", tmp->command[i++]);
			}
			printf("\n");
		}
	}
	// else
	// 	redirect();
}

void	cd(t_args *args)
{
	int		val;
	char	*str;
	char	*str1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (args->command[1] == NULL)
	{
		str = getcwd(0, 0);
		while (j != 3)
		{
			if (str[i] == '/')
				j++;
			i++;
		}
		str1 = malloc(i);
		ft_strlcpy(str1, str, i);
		free(str);
		val = chdir(str1);
		if (val < 0)
		{
			perror("cd");
			return ;
		}
		return ;
	}
	val = chdir(args->command[1]);
	if (val < 0)
	{
		str = getcwd(0, 0);
		i = ft_strlen(str);
		j = ft_strlen(args->command[1]);
		str1 = malloc(i + j + 1);
		str1 = ft_strcpy(str1, str);
		str1[i] = '/';
		str1[i + 1] = '\0';
		str1 = ft_strjoin(str1, args->command[1]);
		val = chdir(str1);
		free(str1);
		if (val < 0)
			perror("cd");
	}
}

void	pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	printf("%s\n", str);
	free(str);
}

void	ft_exit(void)
{
	ft_putendl_fd("gggggggsdagdash", 2);
	exit(0);
}

void	env(void)
{
	t_env	*tmp;

	tmp = glo.env;
	while (tmp)
	{
		printf("%s  ", tmp->name);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

char	*add_eq(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(str) + 2);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '=';
	ret[i + 1] = 0;
	return (ret);
}

void ft_unset(char	**str)
{
	t_env	*tmp;
	t_env	*tmp1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		str[i] = add_eq(str[i]);
		i++;
	}
	i = 0;
	while (str[i])
	{
		tmp = glo.env;
		tmp1 = glo.env;
		while (tmp1)
		{
			if (ft_strlen(str[i]) == ft_strlen(tmp1->name))
			{
				if (ft_strcmp(str[i], tmp1->name) == 1)
				{
					tmp->next = tmp1->next;
					break ;
				}
			}
			if (j > 0)
				tmp = tmp->next;
			tmp1 = tmp1->next;
			j++;
		}
		if (tmp1)
		{
			free(tmp1->name);
			free(tmp1->value);
			free(tmp1);
		}
		i++;
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
	t_env	*tmp = glo.env;

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
	t_args	*tmp1;
	t_env	*ret;
	char	**hol;
	int		i;

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
	if (check_for_export(str) < 0)
		return ;
	i = 0;
	tmp = glo.env;
	hol = ft_split(str, '=');
	hol[0] = ft_strjoin(hol[0], "=");
	while (tmp)
	{
		if (ft_strlen(tmp->name) == ft_strlen(hol[0]))
		{
			if (ft_strcmp(hol[0], tmp->name) == 1)
				break ;
		}
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(hol[1])	;
		while (hol[i])
			free(hol[i++]);
		free(hol);
		return ;
	}
	add_new_var(hol[0], hol[1]);
	while (hol[i])
		free(hol[i++]);
	free(hol);
}