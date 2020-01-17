/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:41:19 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:41:21 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	prep_spi(t_wrap *wrap, int t[14], double d[2])
{
	t[0] = (int)((wrap->cub->rw / 2) * (1 + d[0] / d[1]));
	t[1] = (int)(0.0 / d[1]);
	t[2] = abs((int)(wrap->cub->rh / d[1]));
	t[3] = -1 * t[2] / 2 + wrap->cub->rh / 2 + t[1];
	if (t[3] < 0)
		t[3] = 0;
	t[4] = t[2] / 2 + wrap->cub->rh / 2 + t[1];
	if (t[4] >= wrap->cub->rh)
		t[4] = wrap->cub->rh;
	t[5] = abs((int)(wrap->cub->rh / d[1]));
	t[6] = -1 * t[5] / 2 + t[0];
	if (t[6] < 0)
		t[6] = 0;
	t[7] = t[5] / 2 + t[0];
	if (t[7] >= wrap->cub->rw)
		t[7] = wrap->cub->rw - 1;
	t[8] = t[6];
}

void	prep_spd(t_wrap *wrap, double d[2], int i, int t[14])
{
	double d0;
	double d1;
	double d2;

	d0 = wrap->cub->sx[i] + 0.5 - wrap->game->posx;
	d1 = wrap->cub->sy[i] + 0.5 - wrap->game->posy;
	d2 = 1.0 / (wrap->game->planex * wrap->game->diry - wrap->game->dirx
	* wrap->game->planey);
	d[0] = d2 * (wrap->game->diry * d0 - wrap->game->dirx * d1);
	d[1] = d2 * (-1 * wrap->game->planey * d0 + wrap->game->planex * d1);
	prep_spi(wrap, t, d);
}

void	deal_sprite(t_wrap *wrap, int i, double *zbuffer)
{
	double	d[2];
	int		t[14];

	prep_spd(wrap, d, i, t);
	while (t[8] < t[7] + 1)
	{
		t[9] = (int)(256 * (t[8] - (-t[5] / 2 + t[0])) *
		(wrap->img[4].nbc) / t[5]) / 256;
		if (d[1] > 0 && t[8] >= 0 && t[8] < wrap->cub->rw &&
		d[1] < zbuffer[t[8]])
		{
			t[12] = t[3];
			while (t[12] < t[4])
			{
				t[11] = (t[12] - t[1]) * 256 - wrap->cub->rh * 128 + t[2] * 128;
				t[10] = ((t[11] * (wrap->img[4].nbl - 1)) / t[2]) / 256;
				t[13] = pick_color(wrap->img[4], t[10] + 1, t[9] + 1);
				if (t[13] >= 0)
					mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win,
					t[8], t[12], t[13]);
				t[12]++;
			}
		}
		t[8]++;
	}
}

void	fct_test(t_wrap *wrap)
{
	int		w;
	double	pos_x;
	double	pos_y;
	double	zbuffer[wrap->cub->rw];
	int		x;

	w = wrap->cub->rw;
	pos_x = wrap->game->posx;
	pos_y = wrap->game->posy;
	x = 0;
	while (x < w)
	{
		deal_wall(wrap, x, zbuffer);
		x++;
	}
	sort_sprite(wrap->cub, pos_x, pos_y);
	x = 0;
	while (wrap->cub->sx[x] >= 0)
	{
		deal_sprite(wrap, x, zbuffer);
		x++;
	}
	mlx_loop(wrap->data->mlx_ptr);
}
