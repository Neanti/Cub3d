/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:36:31 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 12:36:33 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	place_n(t_info *game, int i, int j)
{
	game->posx = i + 0.5;
	game->posy = j + 0.5;
	game->dirx = -1;
	game->diry = 0;
	game->planex = 0;
	game->planey = 0.66;
	game->starto = -1;
}

void	place_e(t_info *game, int i, int j)
{
	game->posx = i + 0.5;
	game->posy = j + 0.5;
	game->dirx = 0;
	game->diry = 1;
	game->planey = 0;
	game->planex = 0.66;
	game->starto = -1;
}

void	place_w(t_info *game, int i, int j)
{
	game->posx = i + 0.5;
	game->posy = j + 0.5;
	game->dirx = 0;
	game->diry = -1;
	game->planey = 0;
	game->planex = 0.66;
	game->starto = 1;
}

void	place_s(t_info *game, int i, int j)
{
	game->posx = i + 0.5;
	game->posy = j + 0.5;
	game->dirx = 1;
	game->diry = 0;
	game->planex = 0;
	game->planey = 0.66;
	game->starto = 1;
}

void	locate_player(t_info *game, t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N')
				place_n(game, i, j);
			else if (cub->map[i][j] == 'E')
				place_e(game, i, j);
			else if (cub->map[i][j] == 'W')
				place_w(game, i, j);
			else if (cub->map[i][j] == 'S')
				place_s(game, i, j);
			j++;
		}
		i++;
	}
}
