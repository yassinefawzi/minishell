/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linaina <linaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:03:35 by linaina           #+#    #+#             */
/*   Updated: 2023/08/28 23:47:21 by linaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    clean_node(int j)
{
    int i = 0;
    t_env   *tmp;
    t_env     *hol;

    tmp = glo.env;
    if(j == 0)
    {
        hol = tmp;
        glo.env = tmp->next;
        free(hol->name);
        free(hol->value);
        free(hol);
        return ;
    }
    while (i < j)
    {
        if(i == j - 1) 
            break;
        tmp = tmp->next;
        i++;
    }
    hol = tmp->next;
    tmp->next = tmp->next->next;
    free(hol->name);
    free(hol->value);
    free(hol);
}

void    ft_unset(char **cmd)
{
    t_env   *tmp;
    int     i;
    int     j;

    if (!cmd[1])
        return ;
    i = 0;
    while (cmd[i])
    {
        cmd[i] = ft_strjoin(cmd[i], "=");
        i++;
    }
    i = 1;
    while (cmd[i])
    {
        tmp = glo.env;
        j = 0;
        while (tmp)
        {
            if (ft_strcmp(tmp->name, cmd[i]) > 0)
            {
                clean_node(j);
                break ;
            }
            j++;
            tmp = tmp->next;
        }
        i++;
    }
}