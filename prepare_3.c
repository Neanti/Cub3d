/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:38:59 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:39:01 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_info	prepare_info(void)
{
	t_info i;

	i.posX = 12;
	i.posY = 12;
	i.dirX = -1;
	i.dirY = 0;
	i.planeX = 0.66;
	i.planeY = 0;
	return (i);
}

char	**prep_out_space(int i, int m)
{
	char **out;

	if ((out = malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	out[i] = 0;
	while (i > 0)
	{
		if ((out[i - 1] = malloc(sizeof(char) * (m + 1))) == NULL)
			return (NULL);
		ft_bzero(out[i - 1], m);
		i--;
	}
	return (out);
}

int		count_space(char **s, int *i)
{
	int j;
	int m;

	*i = 0;
	j = 0;
	m = 0;
	while (s[*i])
	{
		j = 0;
		while (s[*i][j])
		{
			j++;
		}
		m = (m > j) ? m : j;
		(*i)++;
	}
	return (m);
}

char	**remove_space(char **s, int *x, int *y)
{
	char	**out;
	int		i;
	int		j;

	*x = count_space(s, &i);
	out = prep_out_space(i, *x);
	i = 0;
	while (s[i] && !(j = 0))
	{
		*x = 0;
		while (s[i][j])
		{
			if (s[i][j] != ' ')
			{
				out[i][*x] = s[i][j];
				(*x)++;
			}
			j++;
		}
		i++;
	}
	*x = i;
	*y = (j + 1) / 2;
	ft_split_free(s);
	return (out);
}

void	locate_sprite(t_cub *cub)
{
	int *x;
	int *y;
	int i;
	int j;
	int k;

	x = malloc(sizeof(int) * (count_sprite(cub->map) + 1));
	y = malloc(sizeof(int) * (count_sprite(cub->map) + 1));
	k = 0;
	x[count_sprite(cub->map)] = -1;
	y[count_sprite(cub->map)] = -1;
	i = -1;
	while (cub->map[++i] != NULL && !(j = 0))
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '2')
			{
				x[k] = i;
				y[k] = j;
				k++;
			}
			j++;
		}
	cub->sx = x;
	cub->sy = y;
}
