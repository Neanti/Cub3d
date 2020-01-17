/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:06:59 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 12:07:00 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	prep_no(t_wrap *wrap, int t[7])
{
	t[0] = (int)wrap->game->posx;
	t[1] = (int)wrap->game->posy;
	t[4] = 0;
}

void	prep_nod(t_wrap *wrap, double d[7], int x, int t[7])
{
	d[0] = wrap->game->dirx + wrap->game->planex * (2 *
	x / (double)wrap->cub->rw - 1);
	d[1] = wrap->game->diry + wrap->game->planey * (2 *
	x / (double)wrap->cub->rw - 1);
	d[4] = fabs(1 / d[0]);
	d[5] = fabs(1 / d[1]);
	if (d[0] < 0 && (t[2] = -1))
		d[2] = (wrap->game->posx - t[0]) * d[4];
	else if ((t[2] = 1))
		d[2] = (t[0] + 1.0 - wrap->game->posx) * d[4];
	if (d[1] < 0)
	{
		t[3] = -1;
		d[3] = (wrap->game->posy - t[1]) * d[5];
	}
	else if ((t[3] = 1))
		d[3] = (t[1] + 1.0 - wrap->game->posy) * d[5];
	t[6] = x;
}

double	*deal_wall(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw])
{
	int		t[7];
	double	d[7];

	prep_no(wrap, t);
	prep_nod(wrap, d, x, t);
	while (t[4] == 0)
	{
		if (d[2] < d[3] && !(t[5] = 0))
			deal_side(&d[2], d[4], &t[0], t[2]);
		else
			t[5] = deal_side(&d[3], d[5], &t[1], t[3]);
		t[4] = (wrap->cub->map[t[0]][t[1]] - 48 == 1) ? 1 : t[4];
		d[6] = (t[5] == 0) ? calc_wall(t[0], wrap->game->posx, t[2], d[0]) :
		calc_wall(t[1], wrap->game->posy, t[3], d[1]);
		de(wrap, zbuffer, t, d);
	}
	return (zbuffer);
}
