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

double part_one(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw])
{
	double camera_x = 2 * x / (double)wrap->cub->rw - 1;
	double raydir_x = wrap->game->dirX + wrap->game->planeX * camera_x;
	double raydir_y = wrap->game->dirY + wrap->game->planeY * camera_x;
	int map_x = (int)wrap->game->posX;
	int map_y = (int)wrap->game->posY;
	double sdist_x;
	double sdist_y;
	double ddist_x = fabs(1 / raydir_x);
	double ddist_y = fabs(1 / raydir_y);
	double wall_dist;
	double pos_x = wrap->game->posX;
	double pos_y = wrap->game->posY;
	int step_x;
	int step_y;

	int hit = 0;
	int side;
	if (raydir_x < 0)
	{
		step_x = -1;
		sdist_x = (pos_x - map_x) * ddist_x;
	}
	else if ((step_x = 1))
		sdist_x = (map_x + 1.0 - pos_x) * ddist_x;
	if (raydir_y < 0)
	{
		step_y = -1;
		sdist_y = (pos_y - map_y) * ddist_y;
	}
	else if ((step_y = 1))
		sdist_y = (map_y + 1.0 - pos_y) * ddist_y;
	int i = 0;
	while (hit == 0)
	{
		if (sdist_x < sdist_y)
		{
			sdist_x += ddist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			sdist_y += ddist_y;
			map_y += step_y;
			side = 1;
		}
		if (wrap->cub->map[map_x][map_y] - 48 == 1)
			hit = 1;
		if (side == 0)
			wall_dist = (map_x - pos_x + (1 - step_x) / 2) / raydir_x;
		else
			wall_dist = (map_y - pos_y + (1 - step_y) / 2) / raydir_y;

		int l_height = (int)(wrap->cub->rh / wall_dist);

		int d_start = -l_height / 2 + wrap->cub->rh / 2;
		int d_end = l_height / 2 + wrap->cub->rh / 2;
		int color;
		double wallx;
		if (side == 0)
			wallx = pos_y + wall_dist * raydir_y;
		else
			wallx = pos_x + wall_dist * raydir_x;
		wallx -= floor((wallx));
		int tex_x = (int)(wallx * (double)wrap->img[4].nbc);
		if (side == 0 && raydir_x > 0)
			tex_x = wrap->img[0].nbc - tex_x - 1;
		if (side == 1 && raydir_y < 0)
			tex_x = wrap->img[0].nbc - tex_x - 1;
		int nbt;
		if (raydir_x > 0)
			nbt = 0;
		else
			nbt = 1;
		if (side == 1 && raydir_y > 0)
			nbt = 2;
		else if (side == 1)
			nbt = 3;
		if (hit == 1)
			ft_put_line(ft_pack(x, d_start, d_end, wrap->cub->rh), nbt, wallx, wrap);
		zbuffer[x] = wall_dist;
	}
}

void fct_test(int key, t_wrap *wrap)
{
	int w = wrap->cub->rw;
	int h = wrap->cub->rh;
	double pos_x = wrap->game->posX;
	double pos_y = wrap->game->posY;
	double dir_x = wrap->game->dirX;
	double dir_y = wrap->game->dirY;
	double plane_x = wrap->game->planeX;
	double plane_y = wrap->game->planeY;

	double zbuffer[wrap->cub->rw];
	int x;

	x = 0;
	while (x < w)
	{
		part_one(wrap, x, zbuffer);
		// double camera_x = 2 * x / (double)w - 1;
		// double raydir_x = dir_x + plane_x * camera_x;
		// double raydir_y = dir_y + plane_y * camera_x;
		// int map_x = (int)pos_x;
		// int map_y = (int)pos_y;
		// double sdist_x;
		// double sdist_y;
		// double ddist_x = fabs(1 / raydir_x);
		// double ddist_y = fabs(1 / raydir_y);
		// double wall_dist;

		// int step_x;
		// int step_y;

		// int hit = 0;
		// int side;
		// if (raydir_x < 0)
		// {
		// 	step_x = -1;
		// 	sdist_x = (pos_x - map_x) * ddist_x;
		// }
		// else if ((step_x = 1))
		// 	sdist_x = (map_x + 1.0 - pos_x) * ddist_x;
		// if (raydir_y < 0)
		// {
		// 	step_y = -1;
		// 	sdist_y = (pos_y - map_y) * ddist_y;
		// }
		// else if ((step_y = 1))
		// 	sdist_y = (map_y + 1.0 - pos_y) * ddist_y;
		// int i = 0;
		// while (hit == 0)
		// {
		// 	if (sdist_x < sdist_y)
		// 	{
		// 		sdist_x += ddist_x;
		// 		map_x += step_x;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sdist_y += ddist_y;
		// 		map_y += step_y;
		// 		side = 1;
		// 	}
		// 	if (wrap->cub->map[map_x][map_y] - 48 == 1)
		// 		hit = 1;
		// 	if (side == 0)
		// 		wall_dist = (map_x - pos_x + (1 - step_x) / 2) / raydir_x;
		// 	else
		// 		wall_dist = (map_y - pos_y + (1 - step_y) / 2) / raydir_y;

		// 	int l_height = (int)(h / wall_dist);

		// 	int d_start = -l_height / 2 + h / 2;
		// 	int d_end = l_height / 2 + h / 2;
		// 	int color;
		// 	double wallx;
		// 	if (side == 0)
		// 		wallx = pos_y + wall_dist * raydir_y;
		// 	else
		// 		wallx = pos_x + wall_dist * raydir_x;
		// 	wallx -= floor((wallx));
		// 	int tex_x = (int)(wallx * (double)wrap->img[4].nbc);
		// 	if (side == 0 && raydir_x > 0)
		// 		tex_x = wrap->img[0].nbc - tex_x - 1;
		// 	if (side == 1 && raydir_y < 0)
		// 		tex_x = wrap->img[0].nbc - tex_x - 1;
		// 	int nbt;
		// 	if (raydir_x > 0)
		// 		nbt = 0;
		// 	else
		// 		nbt = 1;
		// 	if (side == 1 && raydir_y > 0)
		// 		nbt = 2;
		// 	else if (side == 1)
		// 		nbt = 3;
		// 	if (hit == 1)
		// 		ft_put_line(ft_pack(x, d_start, d_end, h), nbt, wallx, wrap);
		// 	zbuffer[x] = wall_dist;
		// }
		x++;
	}
	sort_sprite(wrap->cub, pos_x, pos_y);
	int i;

	i = 0;
	while (wrap->cub->sx[i] >= 0)
	{
		double sp = ((pos_x - wrap->cub->sx[i]) * (pos_x - wrap->cub->sx[i]) + (pos_y - wrap->cub->sy[i]) * (pos_y - wrap->cub->sy[i]));
		double sprite_x = wrap->cub->sx[i] + 0.5 - pos_x;
		double sprite_y = wrap->cub->sy[i] + 0.5 - pos_y;
		double i_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
		double transform_x = i_det * (dir_y * sprite_x - dir_x * sprite_y);
		double transform_y = i_det * (-1 * plane_y * sprite_x + plane_x * sprite_y);
		int sp_sc_x = (int)((w / 2) * (1 + transform_x / transform_y));
		int v_move_sc = (int)(0.0 / transform_y);
		int spr_height = abs((int)(h / transform_y));
		int d_start_y = -1 * spr_height / 2 + h / 2 + v_move_sc;
		if (d_start_y < 0)
			d_start_y = 0;
		int d_end_y = spr_height / 2 + h / 2 + v_move_sc;
		if (d_end_y >= h)
			d_end_y = h;
		int spr_width = abs((int)(h / transform_y));
		int d_start_x = -1 * spr_width / 2 + sp_sc_x;
		if (d_start_x < 0)
			d_start_x = 0;
		int d_end_x = spr_width / 2 + sp_sc_x;
		if (d_end_x >= w)
			d_end_x = w - 1;
		for (int stripe = d_start_x; stripe < d_end_x + 1; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-spr_width / 2 + sp_sc_x)) * (wrap->img[4].nbc) / spr_width) / 256;
			if (transform_y > 0 && stripe >= 0 && stripe < w && transform_y < zbuffer[stripe])
			{
				int y = d_start_y;
				while (y < d_end_y)
				{
					int d = (y - v_move_sc) * 256 - h * 128 + spr_height * 128;
					int tex_y = ((d * (wrap->img[4].nbl - 1)) / spr_height) / 256;
					int color = pick_color(wrap->img[4], tex_y + 1, tex_x + 1);
					if (color >= 0)
						mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win, stripe, y, color);
					y++;
				}
			}
		}
		i++;
	}
	mlx_loop(wrap->data->mlx_ptr);
}
