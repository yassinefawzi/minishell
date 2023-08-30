/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:52:47 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 08:56:22 by yfawzi           ###   ########.fr       */
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
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;	
			if (str[i + 1] && str[i + 1] == '|')
				return (pipnum + 1);
			pipnum++;
		}
		i++;
	}
	return (-1);
}

int	cleaned_len(char *str, int i, int ret, int hol)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = first_quote(str + i, str[i]);
			while (str[i++] && hol--)
				ret++;
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (str[i + 1] == ' ' || str[i] == '\t')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				ret++;
			}
		}
		ret++;
		if (str[i])
			i++;
	}
	return (ret);
}

char	*ft_clean(char *str, int i, int j)
{
	char	*ret;
	int		hol;

	ret = malloc(cleaned_len(str, 0, 0, 0) + 1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = first_quote(str + i, str[i]);
			while (str[i] && hol--)
				ret[j++] = str[i++];
		}
		if (str[i] == ' ' && str[i] == '\t')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
		}
		ret[j++] = str[i++];
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

int	ft_spaces_len_norm(char *str, int i, int ret)
{
	if (i > 0)
	{
		if (str[i - 1] == ' ' || str[i - 1] == '\t')
			ret--;
	}
	return (ret);
}

int	ft_spaces_len(char	*str, int i, int ret, char hol)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			hol = str[i++];
			while (str[i] && str[i] != hol)
			{
				ret++;
				i++;
			}
			ret++;
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))
				i++;
		}
		if (str[i])
			i++;
		ret++;
	}
	if (str)
		ret = ft_spaces_len_norm(str, i, ret);
	return (ret);
}

int	cleaned_spaces_norm(char *str, int i)
{
	while (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))
		i++;
	if ((str[i] == ' ' || str[i] == '\t') && !str[i + 1])
		i++;
	return (i);
}

char	*cleaned_spaces(char *str, int i, int j, int k)
{
	char	*ret;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	ret = malloc(ft_spaces_len(str, 0, 0, 0) + 1);
	while (str[i])
	{
		if (!str[i + 1]  && (str[i] == ' ' || str[i] == '\t'))
				break ;
		if (str[i] == '\'' || str[i] == '"')
		{
			k = quote_len(str, i) + 2;
			while (k--)
				ret[j++] = str[i++];
		}
		if (str[i] == ' ' || str[i] == '\t')
			i = cleaned_spaces_norm(str, i);
		if (str[i])
			ret[j++] = str[i++];
	}
	ret[j] = 0;
	free(str);
	return (ret);
}