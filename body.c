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

	raydir_x = wrap->game->dirX + wrap->game->planeX * (2 * x / (double)wrap->cub->rw - 1);
	raydir_y = wrap->game->dirY + wrap->game->planeY * (2 * x / (double)wrap->cub->rw - 1);
	if (side == 0)
		wallx = wrap->game->posY + wall_dist * raydir_y;
	else
		wallx = wrap->game->posX + wall_dist * raydir_x;
	wallx -= floor((wallx));
	return (wallx);
}

double	*deal_wall_one(t_wrap *wrap, double wdist, int side, int x, int hit, double zbuffer[wrap->cub->rw])
{
	int l_height;
	double wallx;
	double dir_x;
	double dir_y;
	int tex_x;

	l_height = (int)(wrap->cub->rh / wdist);
	dir_x = wrap->game->dirX + wrap->game->planeX * (2 * x / (double)wrap->cub->rw - 1);
	dir_y = wrap->game->dirY + wrap->game->planeY * (2 * x / (double)wrap->cub->rw - 1);
	wallx = find_wallx(side, wrap, wdist, x);
	tex_x = (int)(wallx * (double)wrap->img[4].nbc);
	if (side == 0 && dir_x > 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (side == 1 && dir_y < 0)
		tex_x = wrap->img[0].nbc - tex_x - 1;
	if (hit == 1)
		ft_put_line(ft_pack(x, -l_height / 2 + wrap->cub->rh / 2, l_height / 2 + wrap->cub->rh / 2, wrap->cub->rh), nbt(side, dir_x, dir_y), wallx, wrap);
	zbuffer[x] = wdist;
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

double	*deal_wall(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw])
{
	double raydir_x;
	double raydir_y;
	int map_x;
	int map_y;
	double sdist_x;
	double sdist_y;
	double ddist_x;
	double ddist_y;
	double wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;

	raydir_x = wrap->game->dirX + wrap->game->planeX * (2 * x / (double)wrap->cub->rw - 1);
	raydir_y = wrap->game->dirY + wrap->game->planeY * (2 * x / (double)wrap->cub->rw - 1);
	map_x = (int)wrap->game->posX;
	map_y = (int)wrap->game->posY;
	ddist_x = fabs(1 / raydir_x);
	ddist_y = fabs(1 / raydir_y);
	hit = 0;
	if (raydir_x < 0 && (step_x = -1))
		sdist_x = (wrap->game->posX - map_x) * ddist_x;
	else if ((step_x = 1))
		sdist_x = (map_x + 1.0 - wrap->game->posX) * ddist_x;
	if (raydir_y < 0)
	{
		step_y = -1;
		sdist_y = (wrap->game->posY - map_y) * ddist_y;
	}
	else if ((step_y = 1))
		sdist_y = (map_y + 1.0 - wrap->game->posY) * ddist_y;
	while (hit == 0)
	{
		if (sdist_x < sdist_y && !(side = 0))
			deal_side(&sdist_x, ddist_x, &map_x, step_x);
		else
			side = deal_side(&sdist_y, ddist_y, &map_y, step_y);
		hit = (wrap->cub->map[map_x][map_y] - 48 == 1) ? 1 : hit;
		wall_dist = (side == 0) ? calc_wall(map_x, wrap->game->posX, step_x, raydir_x) : calc_wall(map_y, wrap->game->posY, step_y, raydir_y);
		deal_wall_one(wrap, wall_dist, side, x, hit, zbuffer);
	}
	return (zbuffer);
}

void	deal_sprite(t_wrap *wrap, int i, double *zbuffer)
{
	double sprite_x = wrap->cub->sx[i] + 0.5 - wrap->game->posX;
	double sprite_y = wrap->cub->sy[i] + 0.5 - wrap->game->posY;
	double i_det = 1.0 / (wrap->game->planeX * wrap->game->dirY - wrap->game->dirX * wrap->game->planeY);
	double transform_x = i_det * (wrap->game->dirY * sprite_x - wrap->game->dirX * sprite_y);
	double transform_y = i_det * (-1 * wrap->game->planeY * sprite_x + wrap->game->planeX * sprite_y);
	int sp_sc_x = (int)((wrap->cub->rw / 2) * (1 + transform_x / transform_y));
	int v_move_sc = (int)(0.0 / transform_y);
	int spr_height = abs((int)(wrap->cub->rh / transform_y));
	int d_start_y = -1 * spr_height / 2 + wrap->cub->rh / 2 + v_move_sc;
	if (d_start_y < 0)
		d_start_y = 0;
	int d_end_y = spr_height / 2 + wrap->cub->rh / 2 + v_move_sc;
	if (d_end_y >= wrap->cub->rh)
		d_end_y = wrap->cub->rh;
	int spr_width = abs((int)(wrap->cub->rh / transform_y));
	int d_start_x = -1 * spr_width / 2 + sp_sc_x;
	if (d_start_x < 0)
		d_start_x = 0;
	int d_end_x = spr_width / 2 + sp_sc_x;
	if (d_end_x >= wrap->cub->rw)
		d_end_x = wrap->cub->rw - 1;
	for (int stripe = d_start_x; stripe < d_end_x + 1; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-spr_width / 2 + sp_sc_x)) * (wrap->img[4].nbc) / spr_width) / 256;
		if (transform_y > 0 && stripe >= 0 && stripe < wrap->cub->rw && transform_y < zbuffer[stripe])
		{
			int y = d_start_y;
			while (y < d_end_y)
			{
				int d = (y - v_move_sc) * 256 - wrap->cub->rh * 128 + spr_height * 128;
				int tex_y = ((d * (wrap->img[4].nbl - 1)) / spr_height) / 256;
				int color = pick_color(wrap->img[4], tex_y + 1, tex_x + 1);
				if (color >= 0)
					mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win, stripe, y, color);
				y++;
			}
		}
	}
}

void	fct_test(t_wrap *wrap)
{
	int w;
	double pos_x;
	double pos_y;
	double zbuffer[wrap->cub->rw];
	int x;

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
