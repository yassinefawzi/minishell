/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/05/31 03:16:12 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_name(char *str)
{
	int		i;
	char	*str1;

	i = 0;
	while (str[i] != '=')
		i++;
	str1 = malloc(i + 2);
	i = 0;
	while (str[i] != '=')
	{
		str1[i] = str[i];
		i++;
	}
	str1[i] = str[i];
	i++;
	str1[i] = '\0';
	return	(str1);
}

int	val_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i++])
		j++;
	return (j);
}

char	*env_val(char *str)
{
	int		i;
	int		j;
	char	*str1;

	i = val_len(str);
	j = 0;
	str1 = malloc(i + 1);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	while(str[i])
		str1[j++] = str[i++];
	str1[j] = '\0';
	return (str1);
}

t_env	*ft_lstnew(char *enva)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->name = env_name(enva);
	env->value = env_val(enva);
	env->next = 0;
	return (env);
}

t_env	*ret_env(char **enva)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	while (enva[i])
	{
		if (i == 0)
		{
			env = ft_lstnew(enva[i]);
			tmp = env;
		}
		else
			env->next = ft_lstnew(enva[i]);
		
		i++;
	}
	return (tmp);
}

int main(int arc, char **arv, char **enva)
{
	int	i;
	t_env	*envar;

	i = 0;
	// if (arc > 1)
	// {
		envar = ret_env(enva);
		while (envar)
		{
			printf("%s", envar->name);
			printf("%s\n", envar->value);
			envar = envar->next;
		}
		free_list(envar);
	//}
}