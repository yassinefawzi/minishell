/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:52:18 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/20 22:16:57 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ft_lstlast(t_args *list)
{
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

void	ft_lstadd_back(t_args **list, t_args *new)
{
	t_args	*last;

	if (!new)
		return ;
	if (list)
	{
		if (*list)
		{
			last = ft_lstlast(*list);
			last->next = new;
		}
		else
			*list = new;
	}
}

int	quote_looper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (-1);
		else if (str[i] == '\'')
			return (-2);
		i++;
	}
	return (1);
}
int	len_of_quotes(char *str)
{
	int	i;
	int	ret;
	char	hol;

	i = 0;
	ret = i;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = str[i++];
			while (str[i] != hol)
			{
				i++;
				ret++;
			}
			i++;
			ret++;
		}
		else if (str[i])
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	hol;
	char	hol1;
	char	*ret;

	j = 0;
	i = 0;
	hol = 0;
	ret = malloc(len_of_quotes(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!hol)
				hol1 = str[i];
			hol = str[i];
			if (hol == hol1)
				ret[j++] = str[i++];
			else
				ret[j++] = hol1;
			while (str[i] != hol)
				ret[j++] = str[i++];
			i++;
		}
		if (str[i])
		{
			ret[j++] = str[i++];
		}
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

int	len_of_split(char *str)
{
	int		i;
	int		ret;
	char	hol;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			hol = str[i++];
			while (str[i] != hol)
				i++;
			if (str[i])
				i++;
			ret++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			ret++;
		}
		if (str[i])
			i++;
	}
	return (ret);
}

char	check_first(char *str)
{
	int	i;

	i =	0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (str[i]);
		else if (str[i] == '\'' || str[i] == '"')
			return (str[i]);
		i++;
	}
	return (0);
}

int	single_splited_len(char *str, char hol)
{
	int		i;
	char	hol1;
	i = 0;

	hol1 = 0;
	if (hol == ' ')
		hol1 = '\t';
	else if (hol == '\t')
		hol1 = ' ';
	while (str[i] && str[i] != hol)
	{
		if (hol1 && str[i] == hol1)
			break ;
		i++;
	}
	return (i);
}
char	**ret_splited_args(char *str)
{
	int		i;
	int		j;
	char	hol;
	int		k;
	char	**ret;

	if (!str)
		return (0);
	ret = ft_calloc((len_of_split(str) + 2), sizeof(char *));
	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		k = 0;
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = str[i++];
			ret[j] = malloc(single_splited_len(str + i, hol) + 1);
			while (str[i] != hol)
				ret[j][k++] = str[i++];
			ret[j][k] = 0;
			if (str[i])
				i++;
			j++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			ret[j] = malloc(single_splited_len(str + i, str[i - 1]) + 1);
			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
				ret[j][k++] = str[i++];
			if (str[i])
				i++;
			ret[j][k] = 0;
			j++;
		}
		else
		{
			ret[j] = malloc(single_splited_len(str + i, check_first(str + i)) + 1);
			while (str [i] && (str[i] != ' ' && str[i] != '\t') && (str[i] != '\'' || str[i] != '"'))
				ret[j][k++] = str[i++];
			ret[j][k] = 0;
			j++;
		}
	}
	return (ret);
}
t_args	*ft_lstnew_args(char *arg)
{
	t_args	*args;
	int		i;
	int		k;
	int		hol;

	k = 0;
	i = 0;
	arg = added_space(arg);
	i = 0;
	if (!arg)
		return (0);
	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	// arg = remove_quote(arg);
	// k = quote_looper(arg);
	// if (k < 0)
	// {
	// 	if (k == -1)
	// 	args->command = ft_split(arg, '"');
	// 	else
	// 		args->command = ft_split(arg, '\'');
	// }
	// else
	args->command = ret_splited_args(arg);
	i = 0;
	args->red = malloc(3 * sizeof(int *));
	args->next = 0;
	free(arg);
	return (args);
}