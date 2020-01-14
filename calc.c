/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:45:43 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:45:51 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	bulle(t_cub *cub, int i)
{
	int t1;

	t1 = cub->sx[i];
	cub->sx[i] = cub->sx[i + 1];
	cub->sx[i + 1] = t1;
	t1 = cub->sy[i];
	cub->sy[i] = cub->sy[i + 1];
	cub->sy[i + 1] = t1;
}

void	sort_sprite(t_cub *cub, double pos_x, double pos_y)
{
	int		i;
	int		b;
	double	n1;
	double	n2;
	int		t1;

	b = 1;
	i = 0;
	while (b == 1)
	{
		b = 0;
		while (cub->sx[i + 1] >= 0)
		{
			n1 = dist(pos_x, pos_y, cub->sx[i], cub->sy[i]);
			n2 = dist(pos_x, pos_y, cub->sx[i + 1], cub->sy[i + 1]);
			if (n2 > n1)
			{
				b = 1;
				bulle(cub, i);
			}
			i++;
		}
	}
}

double	dist(double pos_x, double pos_y, int sx, int sy)
{
	return (((pos_x - sx) * (pos_x - sx) + (pos_y - sy) * (pos_y - sy)));
}

double	ft_calc_vec(double x, double y, double r_x, double r_y)
{
	double l1;
	double l2;
	double p;
	double co;

	l1 = sqrt(pow(x, 2) + pow(y, 2));
	l2 = sqrt(pow(r_x, 2) + pow(r_y, 2));
	p = x * r_x + y * r_y;
	co = (double)p / (l1 * l2);
	co = acos(co);
	co = co * (180 / M_PI);
	return (co);
}
