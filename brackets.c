/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 03:48:29 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/19 19:05:01 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bracket_counter(char *str, char sym)
{
	int	i;
	int	ret;

	if (!sym)
		return (0);
	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += quote_len(str, i) + 1;
		if (str[i] && str[i] == sym)
			ret++;
		i++;
	}
	return (ret);
}

int	sym_check(char *str, char sym, char sym2)
{
	int	hol;
	int	hol2;
	int	res;

	if (sym == '`')
	{
		hol = bracket_counter(str, sym);
		if (hol % 2 != 0)
			return (-1);
		return (1);
	}
	hol = bracket_counter(str, sym);
	hol2 = bracket_counter(str, sym2);
	res = hol - hol2;
	if (res == 0)
		return (1);
	return (-1);
	
}

int	check_for_brackets(char *str)
{
	int		i;
	char	*syms;

	syms = ft_strdup("()[]{}`");
	i = 0;
	while (syms[i] && i < 6)
	{
		if (sym_check(str, syms[i], syms[i + 1]) < 0)
		{
			error_message("parsing error\n");
			return (-1);
		}
		i += 2;
	}
	free(syms);
	return (1);
}
