/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:15:05 by yfawzi            #+#    #+#             */
/*   Updated: 2023/05/16 01:54:16 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_args args)
{
	int	i;
	int	j;

	if (!args.flags)
		printf("%s\n", args.command);
	if (!args.command)
		printf("\n");
	else
	{
		i = 1;
		j = 0;
		while (args.flags[i])
		{
			if (args.flags[i] != 'n')
			{
				j++;
				break ;
			}
			i++;
		}
		if (j == 1)
			printf("%s %s\n", args.command, args.flags);
		else
			printf("%s", args.command);
	}
}

void	cd(t_args args)
{
	int		val;
	char	*str;
	char	*str1;
	int		i;
	int		j;

	val = chdir(args.command);
	if (val < 0)
	{
		str = getcwd(0, 0);
		
		perror("cd");
	}
}

void	pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	printf("%s\n", str);
	free(str);
}

void	ft_exit(void)
{
	exit(0);
}

void	env(char **enva)
{
	int	i;

	i = 0;
	while (enva[i])
		printf("%s\n", enva[i++]);
}

void ft_unset(char **envp, const char *var_name)
{
    int i = 0;
    while (envp[i])
    {
        if (ft_strcmp(envp[i], var_name) == 0)
        {
            free(envp[i]);
            while (envp[i])
            {
                envp[i] = envp[i + 1];
                i++;
            }
            return;
        }
        i++;
    }
}
