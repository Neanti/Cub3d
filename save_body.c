/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:42:10 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:42:11 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	*s_de(t_wrap *wrap, double zbuffer[wrap->cub->rw],
int t[7], double d[7])
{
	int		l_height;
	double	wallx;
	double	dir_x;
	double	dir_y;
	int		tex_x;

	l_height = (int)(wrap->cub->rh / d[6]);
	dir_x = wrap->game->dirx + wrap->game->planex *
	(2 * t[6] / (double)wrap->cub->rw - 1);
	dir_y = wrap->game->diry + wrap->game->planey *
	(2 * t[6] / (double)wrap->cub->rw - 1);
	wallx = find_wallx(t[5], wrap, d[6], t[6]);
	tex_x = (int)(wallx * (double)wrap->img[4].nbc);
	if (t[5] == 0 && dir_x > 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (t[5] == 1 && dir_y < 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (t[4] == 1)
		s_put_line(ft_pack(t[6], -l_height / 2 + wrap->cub->rh / 2, l_height /
		2 + wrap->cub->rh / 2, wrap->cub->rh),
		nbt(t[5], dir_x, dir_y), wallx, wrap);
	zbuffer[t[6]] = d[6];
	return (zbuffer);
}

double	*s_deal_wall(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw])
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
		s_de(wrap, zbuffer, t, d);
	}
	return (zbuffer);
}

void	s_deal_sprite(t_wrap *wrap, int i, double *zbuffer)
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
					s_pixel_put(ft_pack(0, t[12], t[13], t[8]),
					wrap->out, wrap->cub);
				t[12]++;
			}
		}
		t[8]++;
	}
}

void	s_fct_test(t_wrap *wrap)
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
		s_deal_wall(wrap, x, zbuffer);
		x++;
	}
	sort_sprite(wrap->cub, pos_x, pos_y);
	x = 0;
	while (wrap->cub->sx[x] >= 0)
	{
		s_deal_sprite(wrap, x, zbuffer);
		x++;
	}
}
