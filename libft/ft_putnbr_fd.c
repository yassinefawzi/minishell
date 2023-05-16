/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:50:02 by yfawzi            #+#    #+#             */
/*   Updated: 2022/10/20 21:04:57 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	n1;

	n1 = (long int)n;
	if (n1 < 0)
	{
		n1 *= -1;
		write(fd, "-", 1);
	}
	if (n1 <= 9)
		ft_putchar_fd((n1 + 48), fd);
	else
	{
		ft_putnbr_fd(n1 / 10, fd);
		ft_putnbr_fd(n1 % 10, fd);
	}
}
