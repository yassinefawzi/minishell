/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/29 03:19:06 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_valid(char *str)
{
	int	i;
	int	pipnum;

	i = 0;
	pipnum = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] && str[i + 1] == '|')
			{
				if (str[i + 2] && str[i + 2] == '|')
					error();
				return (pipnum);
			}
			pipnum++;
		}
		i++;
	}
	return (-1);
}

int	len_of_pipes(char *str, int num)
{
	int	i;

	i = 0;
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		i++;
	}
	return (i);
}
char	*fixed_pipes(char *str, int num)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(len_of_pipes(str, num) + 1);
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	free(str);
	return (ret);
}

int	cleaned_len(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == "	")
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '	')
		{
			if (str[i + 1] == ' ' || str[i] == '	')
			{
				while (str[i] == ' ' || str[i] == "	")
					i++;
				ret++;
			}
		}
		ret++;
		i++;
	}
	return (ret);
}

char	*ft_clean(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(cleaned_len(str) + 1);
	while (str[i] == ' ' || str[i] == "	")
		i++;
	while (str[i])
	{
		if (str[i] == ' ' && str[i] == '	')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (ret);
}

t_args	ret_com(char *str)
{
	t_args	*ret_args;
	char	**args;
	int		i;
	int		check_for_double;

	i = 0;
	check_for_double = check_if_valid(str);
	if (check_for_double > 0)
		str = fixed_pipes(str, check_for_double);
	args = ft_split(str, '|');
	while (args[i])
	{
		args[i] = ft_clean(args[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		ft_lstadd_back(ret_args, ft_lstnew_args(args[i]));
	}
	
}

int main(int arc, char **arv, char **enva)
{
	int		i;
	t_env	*envar;
	t_args	*args;
	char	**argums;
	char	*line;
	char	*currdir;

	i = 0;
	while (1)
	{	
		currdir = getcwd(0, 0);
		currdir = ft_strjoin(currdir, " ");
		envar = ret_env(enva);
		line = readline(currdir);
		printf("%s\n", line);
		free(currdir);
		free(line);
		free_list(envar);
	}
}