/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:43:18 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:43:19 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	save_pixel_put(int stripe, int y, int color, char *out, t_cub *cub)
{
	ft_put_int(color, &out, 54 + (((cub->rh - y - 1) * cub->rw) + stripe) * 4);
}

char	*prepare_out(int w, int h)
{
	char	*out;
	int		tailletot;
	int		tailleimg;

	tailletot = (w * h * 4) + 54 / 4;
	tailleimg = w * h;
	out = malloc(sizeof(char) * ((w * h * 4) + 54));
	out[0] = 'B';
	out[1] = 'M';
	ft_put_int(tailletot, &out, 2);
	ft_put_int(54, &out, 10);
	ft_put_int(40, &out, 14);
	ft_put_int(w, &out, 18);
	ft_put_int(h, &out, 22);
	out[26] = (char)1;
	out[27] = (char)0;
	ft_put_int(32, &out, 28);
	ft_put_int(0, &out, 30);
	ft_put_int(tailleimg, &out, 34);
	ft_put_int(1000, &out, 38);
	ft_put_int(1000, &out, 42);
	ft_put_int(0, &out, 46);
	ft_put_int(0, &out, 50);
	return (out);
}

void	save_ft_put_line(int x, int start, int end, t_img *txt, int j, int nbt, double wall_x, char *out, t_cub *cub)
{
	int i;
	int col;
	int color;

	i = 0;
	col = round(wall_x * (txt[nbt].nbc - 1)) + 1;
	while (i < j)
	{
		if (i < start)
			save_pixel_put(x, i, cub->C, out, cub);
		else if (i > end)
			save_pixel_put(x, i, cub->F, out, cub);
		else
		{
			color = pick_color(txt[nbt], (int)round(((i - start) / (double)
			(end - start) * (txt[nbt].nbl - 1))) + 1, col);
			save_pixel_put(x, i, color, out, cub);
		}
		i++;
	}
}

void	ft_put_int(int n, char **s, int of)
{
	int tmp;

	tmp = n;
	tmp = tmp >> 24;
	s[0][3 + of] = (char)tmp;
	tmp = n;
	tmp = tmp >> 16;
	tmp = tmp & 0b00000000000000000000000011111111;
	s[0][2 + of] = (char)tmp;
	tmp = n;
	tmp = tmp >> 8;
	tmp = tmp & 0b00000000000000000000000011111111;
	s[0][1 + of] = (char)tmp;
	tmp = n;
	tmp = tmp & 0b00000000000000000000000011111111;
	s[0][0 + of] = tmp;
}

t_img	*ft_prepare_txt(t_cub cub, data_t data)
{
	t_img	*out;

	out = malloc(sizeof(t_img) * 5);
	out[0].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.NO,
	&(out[0].nbc), &(out[0].nbl));
	out[0].img = mlx_get_data_addr(out[0].img, &(out[0].bpp),
	&(out[0].lsize), &(out[0].endian));
	out[1].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.SO,
	&(out[1].nbc), &(out[1].nbl));
	out[1].img = mlx_get_data_addr(out[1].img, &(out[1].bpp),
	&(out[1].lsize), &(out[1].endian));
	out[2].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.EA,
	&(out[2].nbc), &(out[2].nbl));
	out[2].img = mlx_get_data_addr(out[2].img, &(out[2].bpp),
	&(out[2].lsize), &(out[2].endian));
	out[3].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.WE,
	&(out[3].nbc), &(out[3].nbl));
	out[3].img = mlx_get_data_addr(out[3].img, &(out[3].bpp),
	&(out[3].lsize), &(out[3].endian));
	out[4].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.S,
	&(out[4].nbc), &(out[4].nbl));
	out[4].img = mlx_get_data_addr(out[4].img, &(out[4].bpp),
	&(out[4].lsize), &(out[4].endian));
	return (out);
}
