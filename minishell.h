/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:03:00 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/22 19:00:34 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>
# include "libft/libft.h"

typedef struct t_env
{
	char	*name;
	char	*value;
	struct	t_env	*next;
}	t_env;

typedef struct t_args
{
	char	*command;
	char	*flags;
	struct 	t_args	*next;
}	t_args;

void	env(t_env *enva);
void	ft_exit(void);
void	pwd(void);
void	cd(t_args args);
void	echo(t_args args);
char	*ft_strcpy(char *str, char *str1);
int		ft_strcmp(char *str, char *str1);
void	free_list(t_env *glo);
t_env	*ret_env(char **enva);
char	*env_val(char *str);
int		val_len(char *str);
char	*env_name(char *str);
t_env	*ft_lstnew(char *enva);
#endif