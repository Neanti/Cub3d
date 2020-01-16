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

int		nbt(int side, double raydir_x, double raydir_y)
{
	int nbt;

	if (raydir_x > 0)
		nbt = 0;
	else
		nbt = 1;
	if (side == 1 && raydir_y > 0)
		nbt = 2;
	else if (side == 1)
		nbt = 3;
	return (nbt);
}

double	find_wallx(int side, t_wrap *wrap, double wall_dist, int x)
{
	double wallx;
	double raydir_x;
	double raydir_y;

	raydir_x = wrap->game->dirX + wrap->game->planeX * (2 *
	x / (double)wrap->cub->rw - 1);
	raydir_y = wrap->game->dirY + wrap->game->planeY * (2 *
	x / (double)wrap->cub->rw - 1);
	if (side == 0)
		wallx = wrap->game->posY + wall_dist * raydir_y;
	else
		wallx = wrap->game->posX + wall_dist * raydir_x;
	wallx -= floor((wallx));
	return (wallx);
}

double	*deal_wall_one(t_wrap *wrap, double zbuffer[wrap->cub->rw], int t[7], double d[7])
{
	int		l_height;
	double	wallx;
	double	dir_x;
	double	dir_y;
	int		tex_x;

	l_height = (int)(wrap->cub->rh / d[6]);
	dir_x = wrap->game->dirX + wrap->game->planeX *
	(2 * t[6] / (double)wrap->cub->rw - 1);
	dir_y = wrap->game->dirY + wrap->game->planeY *
	(2 * t[6] / (double)wrap->cub->rw - 1);
	wallx = find_wallx(t[5], wrap, d[6], t[6]);
	tex_x = (int)(wallx * (double)wrap->img[4].nbc);
	if (t[5] == 0 && dir_x > 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (t[5] == 1 && dir_y < 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (t[5] == 1)
		ft_put_line(ft_pack(t[6], -l_height / 2 + wrap->cub->rh / 2, l_height / 2
		+ wrap->cub->rh / 2, wrap->cub->rh),
		nbt(t[5], dir_x, dir_y), wallx, wrap); // CHECK X
	zbuffer[t[6]] = d[6];
	return (zbuffer);
}

int		deal_side(double *sdist, double ddist, int *map, int step)
{
	*sdist = *sdist + ddist;
	*map = *map + step;
	return (1);
}

double	calc_wall(int map, double pos, int step, double raydir)
{
	return ((map - pos + (1 - step) / 2) / raydir);
}

void	prep_no(t_wrap *wrap, int t[6])
{
	t[0] = (int)wrap->game->posX;
	t[1] = (int)wrap->game->posY;
	t[4] = 0;
}

void	prep_nod(t_wrap *wrap, double d[7], int x, int t[7])
{
	d[0] = wrap->game->dirX + wrap->game->planeX * (2 *
	x / (double)wrap->cub->rw - 1);
	d[1] = wrap->game->dirY + wrap->game->planeY * (2 *
	x / (double)wrap->cub->rw - 1);
	d[4] = fabs(1 / d[0]);
	d[5] = fabs(1 / d[1]);
	if (d[0] < 0 && (t[2] = -1))
		d[2] = (wrap->game->posX - t[0]) * d[4];
	else if ((t[2] = 1))
		d[2] = (t[0] + 1.0 - wrap->game->posX) * d[4];
	if (d[1] < 0)
	{
		t[3] = -1;
		d[3] = (wrap->game->posY - t[1]) * d[5];
	}
	else if ((t[3] = 1))
		d[3] = (t[1] + 1.0 - wrap->game->posY) * d[5];
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
		d[6] = (t[5] == 0) ? calc_wall(t[0], wrap->game->posX, t[2], d[0]) :
		calc_wall(t[1], wrap->game->posY, t[3], d[1]);
		deal_wall_one(wrap, zbuffer, t, d);
	}
	return (zbuffer);
}

void	prep_spd(t_wrap *wrap, double d[2], int i, int t[14])
{
	double d0;
	double d1;
	double d2;

	d0 = wrap->cub->sx[i] + 0.5 - wrap->game->posX;
	d1 = wrap->cub->sy[i] + 0.5 - wrap->game->posY;
	d2 = 1.0 / (wrap->game->planeX * wrap->game->dirY - wrap->game->dirX
	* wrap->game->planeY);
	d[0] = d2 * (wrap->game->dirY * d0 - wrap->game->dirX * d1);
	d[1] = d2 * (-1 * wrap->game->planeY * d0 + wrap->game->planeX * d1);
	//prep_spi(wrap, t, d);
}

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

void	deal_sprite(t_wrap *wrap, int i, double *zbuffer)
{
	double	d[2];
	int		t[14];

	prep_spd(wrap, d, i, t);
	prep_spi(wrap, t,d);
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
	pos_x = wrap->game->posX;
	pos_y = wrap->game->posY;
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
