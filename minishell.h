/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:03:00 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/10 15:11:27 by yfawzi           ###   ########.fr       */
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
	int		**red;
	struct 	t_args	*next;
}	t_args;

typedef struct t_glo
{
	t_env	*env;
	t_args	*args;
	int		**expnd;
	int		exp_build;
}	t_glo;
t_glo	glo;

void	pwd(void);
void	ft_exit(void);
void	cd(t_args *args);
void	env(void);
void	echo(t_args *args);
void	export(char *str);
int		val_len(char *str);
char	*env_val(char *str);
char	*env_name(char *str);
char	*ft_clean(char *str);
void	ret_red(t_args *args);
t_env	*ret_env(char **enva);
void	ft_free(t_args *args);
void	free_list(t_env *glo);
int		*ret_index(char **str);
int		cleaned_len(char *str);
t_env	*ft_lstnew(char *enva);
char	*added_space(char *str);
int		check_quotes(char *str);
void	return_symbol(char *str);
void	error_message(char *str);
void	hidden_symbols(char *str);
int		ft_spaces_len(char	*str);
int		check_if_valid(char *str);
char	*cleaned_spaces(char *str);
t_args	*ft_lstnew_args(char *arg);
int		check_for_pipes(char *str);
int		num_of_diction(char **str);
int		num_of_dictions(char **str);
int		quote_len(char	*str, int i);
int		check_for_brackets(char *str);
int		check_for_empty_pipe(char *str);
int		check_for_space_error(char *str);
int		first_quote(char *str, char hol);
int		len_of_pipes(char *str, int num);
char	*fixed_pipes(char *str, int num);
int		ft_strcmp(char *str, char *str1);
char	*ft_strcpy(char *str, char *str1);
int		*check_for_redirections(char **str);
int		bracket_counter(char *str, char sym);
int		sym_check(char *str, char sym, char sym2);
void	ft_lstadd_back(t_args **list, t_args *new);
#endif