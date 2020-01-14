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
	while (s[0] != 0)
	{
		free(s[0]);
		s = s + 1;
	}
	free(s[0]);
}

char	*fusion(char **s)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 1;
	s1 = s[0];
	while (s[i])
	{
		s2 = s1;
		s1 = ft_strjoin(s1, s[i]);
		free(s2);
		i++;
	}
	return (s1);
}

void	ft_put_line(int x, int start, int end, t_img *txt, data_t data, int j, int nbt, double wall_x, t_cub *cub)
{
	int i;
	int col;
	int color;

	i = 0;
	col = round(wall_x * (txt[nbt].nbc - 1)) + 1;
	while (i < j)
	{
		if (i < start)
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, cub->C);
		else if (i > end)
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, cub->F);
		else
		{
			color = pick_color(txt[nbt], (int)round(((i - start) / (double)(end - start) * (txt[nbt].nbl - 1))) + 1, col);
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, color);
		}
		i++;
	}
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
