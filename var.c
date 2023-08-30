/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 05:51:32 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/30 08:32:08 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	find_name_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_isalnum(str[i]) > 0)
		{
			j++;
			i++;
		}
		if (j > 0)
			return (j);
		i++;
	}
	return (0);
}

char	*find_name(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(find_name_len(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			while (ft_isalnum(str[i]) > 0)
				ret[j++] = str[i++];
			ret[j] = 0;
			return (ret);
		}
		i++;
	}
	free(ret);
	return (0);
}

int	num_of_vars(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$')
			{
				while (str[i] == '$')
					i++;
				while (str[i] && str[i] != '$')
					i++;
			}
			if (str[i] == '$' && str[i + 1])
				ret++;
		}
		i++;
	}
	return (ret);
}

int	pre_varlen(char *str)
{
	int	i;
	int	ret;

	if (str[0] == '\0')
		return (0);
	ret = 0;
	i = 0;
	i++;
	if (str[i] == ' ' || str[i] == '$')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '$')
			return (0);
	}
	i = 0;
	while (str[i] && str[i] != '$')
	{
		ret++;
		i++;
	}
	return (ret);
}

char	*ret_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	name = ft_strjoin(name, "=");
	while (tmp)
	{
		if (ft_strlen(tmp->name) == ft_strlen(name))
		{
			if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
			{
				free(name);
				return (tmp->value);
			}
		}
		tmp = tmp->next;
	}
	free(name);
	return (0);
}

char    *first_check(char *ret, char *str, int i)
{
    char    *hol;

    hol = ft_substr(ret_var(glo.env, find_name(str + i)), 0, ft_strlen(ret_var(glo.env, find_name(str))));
	ret = ft_strjoin(ret, hol);
	free(hol);
    return (ret);
}

char	*first_check_k(char *ret, char *str, int i, int k)
{
	char    *hol;

    hol = ft_substr(str, i, k);
	ret = ft_strjoin(ret, hol);
	free(hol);
    return (ret);
}

char	*return_var_ret(char *str, char *ret, int *i, int k, int j)
{
	if (str[j] == '$')
	{
    	ret = first_check(ret, str, j);
		j += find_name_len(str + j) + 1;
	}
	j += k;
	*i = j;
	if (str[j] && str[j] == '$' && str[j + 1])
	{
		ret = ft_strjoin(ret, ret_var(glo.env, find_name(str)));
		j += find_name_len(str + j);
		*i = j;
		if (str[++j])
			k = pre_varlen(str + j);
	}
	if (str[j])
	{
		if (k == 0 && str[j] != '$')
			k++;
        ret = first_check_k(ret, str, j, k);
		j += k;
		*i = j;
		k--;
	}
	return (ret);
}

char	*check_var(char *str, int i, int k, char *hol)
{
	char	*ret;

	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	k = pre_varlen(str);
	if ((size_t)k == ft_strlen(str) || k == -1)
		return (str);
	ret = ft_calloc(k + 1, k + 1);
	while (str[i])
	{
		hol = ft_substr(str, i, k);
		ret = ft_strjoin(ret, hol);
		free(hol);
		if (str[i] == '$' && str[i + 1] == '?')
		{
			hol = ft_itoa(glo.exit_status);
			ret = ft_strjoin(ret, hol);
			i+=2;
			free(hol);
		}
		else
			ret = return_var_ret(str, ret, &i, k, i);
	}
	free(str);
	return (ret);
}
