/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:53:40 by augay             #+#    #+#             */
/*   Updated: 2019/10/09 11:53:43 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	start(long *tmp, long *nb, long *base)
{
	*tmp = 0;
	*base = 1;
	if (*nb < 0)
	{
		*nb = *nb * -1;
		*tmp = 1;
	}
}

static char	*body1(long *tmp, long *base, long *nb, char *out)
{
	int i;

	*base = *base / 10;
	i = 0;
	if (*tmp == 1)
	{
		i++;
		out[0] = '-';
	}
	while (*base >= 10)
	{
		*tmp = *nb / *base;
		*nb = *nb - (*tmp * *base);
		out[i] = *tmp + 48;
		i++;
		*base = *base / 10;
	}
	out[i] = *nb + 48;
	i++;
	out[i] = '\0';
	return (out);
}

char		*ft_itoa(int n)
{
	long	tmp;
	long	base;
	long	nb;
	char	*out;
	int		i;

	nb = (long)n;
	if (nb == 0)
	{
		if ((out = (char*)malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		out[0] = '0';
		out[1] = '\0';
		return (out);
	}
	start(&tmp, &nb, &base);
	i = 0;
	while (base <= nb)
	{
		base = base * 10;
		i++;
	}
	if ((out = (char*)malloc(sizeof(char) * (i + 1 + tmp))) == NULL)
		return (NULL);
	return (body1(&tmp, &base, &nb, out));
}
