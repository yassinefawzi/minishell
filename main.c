/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/08 00:46:25 by yfawzi           ###   ########.fr       */
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
			{
				return (pipnum + 1);
			}
			pipnum++;
		}
		i++;
	}
	return (-1);
}

int	len_of_pipes(char *str, int num)
{
	int	i;

	i = 0;
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		i++;
	}
	return (i);
}

char	*fixed_pipes(char *str, int num)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(len_of_pipes(str, num) + 1);
	while (str[i] && num)
	{
		if (str[i] == '|')
			num--;
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	free(str);
	return (ret);
}

int	first_quote(char *str, char hol)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != hol)
		i++;
	return (i);
}

int	cleaned_len(char *str)
{
	int	i;
	int	ret;
	int	hol;

	ret = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = first_quote(str + i, str[i]);
			while (str[i] && hol)
			{
				i++;
				ret++;
				hol--;
			}
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
		i++;
	}
	return (ret - 1);
}


char	*ft_clean(char *str)
{
	int		i;
	int		j;
	int		check;
	char	*ret;
	int		hol;

	i = 0;
	j = 0;
	check = 0;
	ret = malloc(cleaned_len(str) + 1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			hol = first_quote(str + i, str[i]);
			while (str[i] && hol)
			{
				ret[j] = str[i];
				i++;
				j++;
				hol--;
			}
		}
		if (str[i] == ' ' && str[i] == '\t')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

int	ft_spaces_len(char	*str)
{
	int		i;
	int		ret;
	char	hol;

	ret = 0;
	i = 0;
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
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
		}
		if (str[i])
			i++;
		ret++;
	}
	return (ret);
}

char	*cleaned_spaces(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 0;
	j = 0;
	k = 0;
	ret = malloc(ft_spaces_len(str) + 1);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			k = quote_len(str, i) + 1;
			while (k > 0)
			{
				if (str[i] == '|')
					str[i] = 1;
				ret[j] = str[i];
				i++;
				j++;
				k--;
			}
			i++;
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
		}
		if (str[i])
		{
			if (str[i] == '|')
			{
				ret[j] = str[i];
				j++;
				i++;
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				
			}
			ret[j] = str[i];
			i++;
			j++;
		}
	}
	ret[j] = 0;
	free(str);
	return (ret);
}

int	check_for_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				error_message("parse error near `|'\n");
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	check_for_empty_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (!str[i + 1])
			{
				error_message("pipe error\n");
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

t_args	*ret_com(char *str)
{
	t_args	*ret_args;
	char	**args;
	int		i;
	int		check_for_double;

	i = 0;
	ret_args = 0;
	if (check_quotes(str) < 0)
		return (0);
	str = cleaned_spaces(str);
	if (check_for_pipes(str) < 0 || check_for_empty_pipe(str) < 0)
		return (0);
	check_for_double = check_if_valid(str);
	if (check_for_double >=  0)
	{
		if (check_for_double == 0)
			return (NULL); 
		str = fixed_pipes(str, check_for_double);
	}
	args = ft_split(str, '|');
	while (args[i])
	{
		args[i] = ft_clean(args[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		ft_lstadd_back(&ret_args, ft_lstnew_args(args[i]));
		i++;
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (ret_args);
}

void	ft_printer(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		while (args->command[i])
			printf("%s\n", args->command[i++]);
		i = 0;
		printf("-------------\n");
		args = args->next;
	}
}
void	ft_free(t_args *args)
{
	int		i;
	t_args	*tmp;
	t_args	*tmp1;

	tmp = args;
	i = 0;
	while (tmp)
	{
		while (tmp->command[i])
			free(tmp->command[i++]);
		i = 0;
		free(tmp->command);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}

int main(int arc, char **arv, char **enva)
{
	int		i;
	t_env	*envar;
	t_args	*args;
	char	*line;
	char	*currdir;

	i = 0;
	while (1)
	{	
		currdir = getcwd(0, 0);
		currdir = ft_strjoin(currdir, " ");
		envar = ret_env(enva);
		line = readline(currdir);
		add_history(line);  
		args = ret_com(line);
		ft_printer(args);
		free(currdir);
		ft_free(args);
		free_list(envar);
	}

} 