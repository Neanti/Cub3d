/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:49:41 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:49:42 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	deal_key_1(t_info *g, t_cub *cub)
{
	g->posX += g->dirX * 0.8;
	g->posY += g->dirY * 0.8;
	if (g->posX >= cub->mx - 1 || g->posX <= 1 ||
	g->posY >= cub->my - 1 || g->posY <= 1)
	{
		g->posX -= g->dirX * 0.8;
		g->posY -= g->dirY * 0.8;
	}
}

void	deal_key_2(t_info *game, t_cub *cub)
{
	game->posX -= game->dirX * 0.8;
	game->posY -= game->dirY * 0.8;
	if (game->posX >= cub->mx - 1 || game->posX <= 1 ||
	game->posY >= cub->my - 1 || game->posY <= 1)
	{
		game->posX += game->dirX * 0.8;
		game->posY += game->dirY * 0.8;
	}
}

void	deal_key(int key, t_info *game, t_cub *cub)
{
	if (key == 13 || key == 122)
		deal_key_1(game, cub);
	else if (key == 1 || key == 115)
		deal_key_2(game, cub);
	else if (key == 0 || key == 113)
		rot_vec(-20 * game->startO, game);
	else if (key == 2 || key == 100)
		rot_vec(20 * game->startO, game);
}

int		done(int key, void *a)
{
	t_wrap	*wrap;
	t_info	*game;
	t_data	*data;
	t_cub	*cub;
	t_img	*txt;

	wrap = a;
	game = wrap->game;
	data = wrap->data;
	cub = wrap->cub;
	txt = wrap->img;
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		printf("LEGIt EXIT\n");
		system("leaks a.out");
		exit(0);
		return (0);
	}
	else
		deal_key(key, game, cub);
	fct_test(wrap);
	return (1);
}

int		count_sprite(char **s)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (s[i] != NULL)
	{
		while (s[i][j])
		{
			if (s[i][j] == '2')
				n++;
			j++;
		}
		i++;
		j = 0;
	}
	return (n);
}
