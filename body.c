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

void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt)
{
	if (key == 53)
	{
		mlx_destroy_window(data.mlx_ptr, data.mlx_win);
		return;
	}
	int w = cub->rw;
	int h = cub->rh;
	double posX = game->posX;
	double posY = game->posY;
	double dirX = game->dirX;
	double dirY = game->dirY;
	double planeX = game->planeX;
	double planeY = game->planeY;

	double ZBuffer[cub->rw];

	for (int x = 0; x < w; x++)
	{
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		int i = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cub->map[mapX][mapY] - 48 == 1)
			{
				hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(h / perpWallDist);

			int drawStart = -lineHeight / 2 + h / 2;
			int drawEnd = lineHeight / 2 + h / 2;
			int color;
			double wallX;
			if (side == 0)
				wallX = posY + perpWallDist * rayDirY;
			else
				wallX = posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));
			int texX = (int)(wallX * (double)txt[4].nbc);
			if (side == 0 && rayDirX > 0)
				texX = txt[0].nbc - texX - 1;
			if (side == 1 && rayDirY < 0)
				texX = txt[0].nbc - texX - 1;
			int nbt;
			if (rayDirX > 0)
			{
				nbt = 0;
			}
			else
			{
				nbt = 1;
			}
			if (side == 1 && rayDirY > 0)
			{
				nbt = 2;
			}
			else if (side == 1)
			{
				nbt = 3;
			}
			if (hit == 1)
			{
				ft_put_line(x, drawStart, drawEnd, txt, data, h, nbt, wallX, cub);
			}
			ZBuffer[x] = perpWallDist;
		}
	}
	sort_sprite(cub, posX, posY);
	for (int i = 0; cub->sx[i] >= 0; i++)
	{
		double sp = ((posX - cub->sx[i]) * (posX - cub->sx[i]) + (posY - cub->sy[i]) * (posY - cub->sy[i]));
		double spriteX = cub->sx[i] + 0.5 - posX;
		double spriteY = cub->sy[i] + 0.5 - posY;
		double invDet = 1.0 / (planeX * dirY - dirX * planeY);
		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-1 * planeY * spriteX + planeX * spriteY);
		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));
		int vMoveScreen = (int)(0.0 / transformY);
		int spriteHeight = abs((int)(h / transformY));
		int drawStartY = -1 * spriteHeight / 2 + h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
		if (drawEndY >= h)
			drawEndY = h;
		int spriteWidth = abs((int)(h / transformY));
		int drawStartX = -1 * spriteWidth / 2 + spriteScreenX ;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = w - 1;
		for (int stripe = drawStartX; stripe < drawEndX + 1; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * (txt[4].nbc) / spriteWidth) / 256;
			if (transformY > 0 && stripe >= 0 && stripe < w && transformY < ZBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128;
					int texY = ((d * (txt[4].nbl -1)) / spriteHeight) / 256;
					int color = pick_color(txt[4], texY + 1, texX + 1);
					if (color >= 0)
						mlx_pixel_put(data.mlx_ptr, data.mlx_win, stripe, y, color);
				}
			}
		}
	}
	mlx_loop(data.mlx_ptr);
}
