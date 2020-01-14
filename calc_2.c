/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:04:40 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 11:04:42 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rot_vec(double a, t_info *game)
{
	double old;

	old = game->dirX;
	game->dirX = cos(d2r(a)) * game->dirX - sin(d2r(a)) * game->dirY;
	game->dirY = sin(d2r(a)) * old + cos(d2r(a)) * game->dirY;
	old = game->planeX;
	game->planeX = cos(d2r(a)) * game->planeX - sin(d2r(a)) * game->planeY;
	game->planeY = sin(d2r(a)) * old + cos(d2r(a)) * game->planeY;
}

double	d2r(double d)
{
	double r;

	r = d * (M_PI / 180);
	return (r);
}
