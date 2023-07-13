/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:31:48 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/13 11:36:07 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ret_index(char **str)
{
	int		*ret;
	int		i;
	int		j;

	if (!str)
		return (0);
	j = 0;
	i = num_of_diction(str);
	if (i == 0)
	{
		ret = malloc(sizeof(int));
		ret[0] = 0;
		return (ret);
	}
 	ret = malloc(num_of_diction(str) * sizeof(int));
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' && str[i + 1][0] == '>')
		{
			i++;
			ret[j++] = i + 1;
		}
		else if (str[i][0] == '>' || str[i][0] == '<')
			ret[j++] = i + 1;
		i++;
	}
	if (!ret)
	{
		ret[0] = 0;
	}
	return (ret);
}

void	ret_red(t_args *args)
{
	t_args	*tmp;

	tmp = args;
	while (tmp)
	{
		tmp->red[0] = malloc(sizeof(int));
		tmp->red[0][0] = num_of_diction(tmp->command);
		tmp->red[1] = check_for_redirections(tmp->command);
		tmp->red[2] = ret_index(tmp->command);
		tmp = tmp->next;
	}
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
				if (str[i] != '<' && str[i + 1] != '>')
				{
					ret[j++] = str[i++];
					ret[j++] = ' ';
				}
			}
		}
		if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i + 1] != str[i]) && (str[i] != '<' && str[i + 1] != '>'))
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
int	num_of_diction(char **str)
{
	int	i;
	int	ret;

	i = 0;
	ret = i;
	while (str[i])
	{
		if (str[i][0] == '>' || str[i][0] == '<')
		{
			if (str[i + 1][0] == '>' || str[i + 1][0] == '<')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int	num_of_dictions(char **str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while(str[i])
	{
		if (str[i][0] == '>' || str[i][0] == '<')
		{
			if (str[i + 1][0] == '>' || str[i + 1][0] == '<')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int	*check_for_redirections(char **str)
{
	int	i;
	int	j;
	int	*ret;

	j = 0;
	i = num_of_dictions(str);
	if (i == 0)
	{
		ret = malloc(sizeof(int));
		ret[0] = 0;
		return (ret);
	}
	ret = malloc (num_of_dictions(str) * sizeof(int));
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '>')
		{
			if (str[i][1] == '>')
				ret[j++] = 3;
			ret[j++] = 1;
		}
		 if (str[i][0] == '<')
		{
			if (str[i][1] == '<')
				ret[j++] = 4;
			else if (str[i][1] == '>')
				ret[j++] = -1;
			ret[j++] = 2;
		}
		i++;
	}
	return (ret);
}