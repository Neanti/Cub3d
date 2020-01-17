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

	old = game->dirx;
	game->dirx = cos(d2r(a)) * game->dirx - sin(d2r(a)) * game->diry;
	game->diry = sin(d2r(a)) * old + cos(d2r(a)) * game->diry;
	old = game->planex;
	game->planex = cos(d2r(a)) * game->planex - sin(d2r(a)) * game->planey;
	game->planey = sin(d2r(a)) * old + cos(d2r(a)) * game->planey;
}

double	d2r(double d)
{
	double r;

	r = d * (M_PI / 180);
	return (r);
}
