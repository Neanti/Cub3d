/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:23:30 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:23:31 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	body2(long *tmp, long *base, long *nb, int fd)
{
	int		i;
	char	c;

	*base = *base / 10;
	i = 0;
	while (*base >= 10)
	{
		*tmp = *nb / *base;
		*nb = *nb - (*tmp * *base);
		c = *tmp + 48;
		write(fd, &c, 1);
		i++;
		*base = *base / 10;
	}
	c = *nb + 48;
	write(fd, &c, 1);
	i++;
}

void		ft_putnbr_fd(int n, int fd)
{
	long	tmp;
	long	base;
	long	nb;

	base = 1;
	nb = (long)n;
	if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	while (base <= nb)
		base = base * 10;
	body2(&tmp, &base, &nb, fd);
}
