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
	g->posx += g->dirx * 0.8;
	g->posy += g->diry * 0.8;
	if (g->posx >= cub->mx - 1 || g->posx <= 1 ||
	g->posy >= cub->my - 1 || g->posy <= 1)
	{
		g->posx -= g->dirx * 0.8;
		g->posy -= g->diry * 0.8;
	}
}

void	deal_key_2(t_info *game, t_cub *cub)
{
	game->posx -= game->dirx * 0.8;
	game->posy -= game->diry * 0.8;
	if (game->posx >= cub->mx - 1 || game->posx <= 1 ||
	game->posy >= cub->my - 1 || game->posy <= 1)
	{
		game->posx += game->dirx * 0.8;
		game->posy += game->diry * 0.8;
	}
}

void	deal_key(int key, t_info *game, t_cub *cub)
{
	if (key == 13 || key == 122)
		deal_key_1(game, cub);
	else if (key == 1 || key == 115)
		deal_key_2(game, cub);
	else if (key == 0 || key == 113)
		rot_vec(-20 * game->starto, game);
	else if (key == 2 || key == 100)
		rot_vec(20 * game->starto, game);
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
