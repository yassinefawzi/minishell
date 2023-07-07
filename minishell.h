/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:03:00 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/06 00:20:43 by yfawzi           ###   ########.fr       */
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
	char	**command;
	struct 	t_args	*next;
}	t_args;

void	pwd(void);
void	ft_exit(void);
void	cd(t_args args);
void	env(t_env *enva);
void	echo(t_args args);
int		val_len(char *str);
char	*env_val(char *str);
char	*env_name(char *str);
t_env	*ret_env(char **enva);
void	free_list(t_env *glo);
t_env	*ft_lstnew(char *enva);
int		check_quotes(char *str);
void	error_message(char *str);
t_args	*ft_lstnew_args(char *arg);
int		quote_len(char	*str, int i);
int		ft_strcmp(char *str, char *str1);
char	*ft_strcpy(char *str, char *str1);
void	ft_lstadd_back(t_args **list, t_args *new);
#endif