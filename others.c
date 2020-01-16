/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:47:59 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:48:00 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_split_free(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*fusion(char **s)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = NULL;
	while (s[i])
	{
		s2 = s1;
		s1 = ft_strjoin(s1, s[i]);
		if (s2 != NULL)
			free(s2);
		i++;
	}
	printf("RET FUSI= %s\n", s1);
	return (s1);
}

void	ft_put_line(t_draw *draw, int nbt, double wall_x, t_wrap *wrap)
{
	int i;
	int col;
	int color;

	i = 0;
	col = round(wall_x * (wrap->img[nbt].nbc - 1)) + 1;
	while (i < draw->j)
	{
		if (i < draw->start)
			mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win,
			draw->x, i, wrap->cub->C);
		else if (i > draw->end)
			mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win,
			draw->x, i, wrap->cub->F);
		else
		{
			color = pick_color(wrap->img[nbt], (int)round(((i - draw->start) /
			(double)(draw->end - draw->start) *
			(wrap->img[nbt].nbl - 1))) + 1, col);
			mlx_pixel_put(wrap->data->mlx_ptr, wrap->data->mlx_win,
			draw->x, i, color);
		}
		i++;
	}
	free(draw);
}

char	**ft_prepare_map(char *m, int *x, int *y)
{
	int		i;
	int		j;
	char	**out;

	i = 0;
	j = 0;
	out = ft_split(m, '\n');
	out = remove_space(out, x, y);
	free(m);
	return (out);
}
