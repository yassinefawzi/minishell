/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:44 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/23 02:54:40 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size * count > SIZE_MAX)
		return (0);
	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, '\0', count * size);
	return (p);
}
