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

void save_fct_test(t_info *game, t_cub *cub, t_img *txt, char *out)
{
	int w = cub->rw;
	int h = cub->rh;
	double pos_x = game->posX;
	double pos_y = game->posY;
	double dir_x = game->dirX;
	double dir_y = game->dirY;
	double plane_x = game->planeX;
	double plane_y = game->planeY;

	double z_buffer[cub->rw];

	for (int x = 0; x < w; x++)
	{
		double camera_x = 2 * x / (double)w - 1;
		double ray_dir_x = dir_x + plane_x * camera_x;
		double ray_dir_y = dir_y + plane_y * camera_x;
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;
		double side_dist_x;
		double side_dist_y;
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (cub->map[map_x][map_y] - 48 == 1)
			{
				hit = 1;
			}
			if (side == 0)
				perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
			else
				perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

			int line_height = (int)(h / perp_wall_dist);

			int draw_start = -line_height / 2 + h / 2;
			int draw_end = line_height / 2 + h / 2;
			double wall_x;
			if (side == 0)
				wall_x = pos_y + perp_wall_dist * ray_dir_y;
			else
				wall_x = pos_x + perp_wall_dist * ray_dir_x;
			wall_x -= floor((wall_x));
			int tex_x = (int)(wall_x * (double)txt[4].nbc);
			if (side == 0 && ray_dir_x > 0)
				tex_x = txt[0].nbc - tex_x - 1;
			if (side == 1 && ray_dir_y < 0)
				tex_x = txt[0].nbc - tex_x - 1;
			int nbt;
			if (ray_dir_x > 0)
				nbt = 0;
			else
				nbt = 1;
			if (side == 1 && ray_dir_y > 0)
				nbt = 2;
			else if (side == 1)
				nbt = 3;
			if (hit == 1)
				save_ft_put_line(x, draw_start, draw_end, txt, h, nbt, wall_x,out, cub);
			z_buffer[x] = perp_wall_dist;
		}
	}
	sort_sprite(cub, pos_x, pos_y);
	for (int i = 0; cub->sx[i] >= 0; i++)
	{
		double sprite_x = cub->sx[i] + 0.5 - pos_x;
		double sprite_y = cub->sy[i] + 0.5 - pos_y;
		double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
		double transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
		double transform_y = inv_det * (-1 * plane_y * sprite_x + plane_x * sprite_y);

		int sprite_sc_x = (int)((w / 2) * (1 + transform_x / transform_y));

		int v_mv_sc = (int)(0.0 / transform_y);

		int sprite_height = abs((int)(h / transform_y));
		int draw_start_y = -1 * sprite_height / 2 + h / 2 + v_mv_sc;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + h / 2 + v_mv_sc;
		if (draw_end_y >= h)
			draw_end_y = h;

		int sprite_width = abs((int)(h / transform_y));
		int draw_start_x = -1 * sprite_width / 2 + sprite_sc_x ;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_sc_x;
		if (draw_end_x >= w)
			draw_end_x = w - 1;
		for (int stripe = draw_start_x; stripe < draw_end_x + 1; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_sc_x)) * (txt[4].nbc) / sprite_width) / 256;

			if (transform_y > 0 && stripe >= 0 && stripe < w && transform_y < z_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = (y-v_mv_sc) * 256 - h * 128 + sprite_height * 128;
					int tex_y = ((d * (txt[4].nbl -1)) / sprite_height) / 256;
					int color = pick_color(txt[4], tex_y + 1, tex_x + 1);
					if (color >= 0)
						save_pixel_put(stripe, y, color, out, cub);
				}
			}
		}
	}
}

