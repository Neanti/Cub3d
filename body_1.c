/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:31:54 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 11:31:55 by augay            ###   ########.fr       */
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

double	*de(t_wrap *wrap, double zbuffer[wrap->cub->rw], int t[7], double d[7])
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
	if (t[4] == 1)
		ft_put_line(ft_pack(t[6], -l_height / 2 + wrap->cub->rh / 2, l_height /
		2 + wrap->cub->rh / 2, wrap->cub->rh),
		nbt(t[5], dir_x, dir_y), wallx, wrap);
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