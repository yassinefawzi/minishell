/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:37:54 by yfawzi            #+#    #+#             */
/*   Updated: 2023/08/19 17:26:57 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (c == 0)
		j++;
	if (s[0] != c)
		j++;
	while (i < (int )(ft_strlen(s) + 1))
	{
		while (s[i] == c && s[i + 1] != c && s[i + 1])
		{
			j++;
			i++;
		}
	i++;
	}
	return (j);
}

static int	comptable(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
		if (s[i] == c)
			return (i);
	}
	return (i);
}

static char	**hautgam(char **s1, const char *s, char c)
{
	int				j;
	int				i;
	unsigned int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			len = comptable(&s[i], c);
			s1[j] = ft_substr(&s[i], 0, len);
			if (!s1[j])
				return (NULL);
			j++;
			i += len - 1;
		}
		i++;
	}
	return (s1);
}

char	**ft_split(const char *s, char c)
{
	int		j;
	char	**s1;

	if (s == NULL)
		return (NULL);
	j = check(s, c);
	s1 = (char **)ft_calloc((j + 1), sizeof(char *));
	if (s1 == NULL)
		return (NULL);
	s1[j] = NULL;
	s1 = hautgam(s1, s, c);
	return (s1);
}
