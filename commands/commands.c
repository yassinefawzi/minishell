/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:15:05 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/18 06:42:11 by yfawzi           ###   ########.fr       */
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

void ft_unset(char *str)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = glo.env;
	str = ft_strjoin(str, "=");
	while (tmp)
	{
		if (ft_strlen(tmp->name) == ft_strlen(str))
		{
			if (ft_strncmp(tmp->name, str, ft_strlen(str)) == 0)
				break ;
		}
		tmp1 = tmp;
		tmp = tmp->next;
	}
	if (tmp->next)
		tmp1 = tmp->next;
	else
		tmp1 = 0;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
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

void	export(char *str)
{
	t_env	*tmp;
	t_args	*tmp1;
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
	while(hol[i])
		hol[1] = ft_strjoin(hol[1], hol[i++]);
	hol[0] = ft_strjoin(hol[0], "=");
	i = 0;
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
	if (i == 1)
	{
		free(tmp->value);
		tmp->value = ft_substr(hol[1], 0, ft_strlen(hol[1]));
		return ;
	}
	ret = malloc(sizeof(t_env));
	ret->name = hol[0];
	ret->value = hol[1];
	ret->next = 0;
	tmp->next = ret;
}