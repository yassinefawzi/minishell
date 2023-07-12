/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:52:18 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/12 10:48:44 by yfawzi           ###   ########.fr       */
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

// char	*cleaned_quote(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*ret;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	ret = malloc(ft_strlen(str));
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 			i++;
// 		ret[j++] = str[i++];
// 	}
// 	ret[j] = 0;
// 	return (ret);
// }

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

int	count_space_for_redirection(char *str)
{
	int		i;
	char	hol;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			hol = str[i];
			if (str[i + 1] != hol || str[i - 1] != hol)
			{
				if (str[i + 1] != ' ' && str[i + 1] != '\t')
					j++;
				if (str[i - 1] != ' ' && str[i - 1] != '\t')
					j++;
			}
		}
		i++;
	}
	return (i + j);
}
char	*added_space(char *str)
{
	int		i;
	int		j;
	char	*ret;
	char	hol;

	if (!str)
		return (0);
	i = 0;
	j = i;
	ret = malloc(count_space_for_redirection(str) + 1);
	while (str[i])
	{
		if (str[i + 1] == '>' || str[i + 1] == '<')
		{
			if ((str[i] != ' ' && str[i] != '\t' && str[i] != str[i + 1]))
			{
				ret[j++] = str[i++];
				ret[j++] = ' ';
			}
		}
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] != str[i])
			{
				if (str[i + 1] != ' ' && str[i + 1] != '\t')
				{
					ret[j++] = str[i++];
					ret[j++] = ' ';
				}
			}
		}
		ret[j++] = str[i++];
	}
	ret[j] = 0;
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
	printf("arg == %s\n", arg);
	i = 0;
	if (!arg)
		return (0);
	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	k = quote_looper(arg);
	if (k < 0)
	{
		if (k == -1)
			args->command = ft_split(arg, '"');
		else
			args->command = ft_split(arg, '\'');
	}
	else
		args->command = ft_split(arg, ' ');
	args->next = 0;
	args->red = check_for_redirections(arg);
	args->red_index = 0;
	return (args);
}