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

void	s_pixel_put(t_draw *draw, char *out, t_cub *cub)
{
	ft_put_int(draw->end, &out, 54 + (((cub->rh - draw->start - 1) * cub->rw)
	+ draw->j) * 4);
	free(draw);
}

char	*prepare_out(int w, int h)
{
	char	*out;
	int		tailletot;
	int		tailleimg;

	tailletot = (w * h * 4) + 54 / 4;
	tailleimg = w * h;
	if ((out = malloc(sizeof(char) * ((w * h * 4) + 54))) == NULL)
		exit(er_mem());
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

void	s_put_line(t_draw *draw, int nbt, double wall_x, t_wrap *wrap)
{
	int i;
	int col;
	int color;

	i = 0;
	col = round(wall_x * (wrap->img[nbt].nbc - 1)) + 1;
	while (i < draw->j)
	{
		if (i < draw->start)
			s_pixel_put(ft_pack(0, i, wrap->cub->c, draw->x),
			wrap->out, wrap->cub);
		else if (i > draw->end)
			s_pixel_put(ft_pack(0, i, wrap->cub->f, draw->x),
			wrap->out, wrap->cub);
		else
		{
			color = pick_color(wrap->img[nbt],
			(int)round(((i - draw->start) / (double)
			(draw->end - draw->start) * (wrap->img[nbt].nbl - 1))) + 1, col);
			s_pixel_put(ft_pack(0, i, color, draw->x), wrap->out, wrap->cub);
		}
		i++;
	}
	free(draw);
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

t_img	*ft_prepare_txt(t_cub cub, t_data data)
{
	t_img	*out;

	if ((out = malloc(sizeof(t_img) * 5)) == NULL)
		exit(er_mem());
	out[0].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.no,
	&(out[0].nbc), &(out[0].nbl));
	out[0].img = mlx_get_data_addr(out[0].img, &(out[0].bpp),
	&(out[0].lsize), &(out[0].endian));
	out[1].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.so,
	&(out[1].nbc), &(out[1].nbl));
	out[1].img = mlx_get_data_addr(out[1].img, &(out[1].bpp),
	&(out[1].lsize), &(out[1].endian));
	out[2].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.ea,
	&(out[2].nbc), &(out[2].nbl));
	out[2].img = mlx_get_data_addr(out[2].img, &(out[2].bpp),
	&(out[2].lsize), &(out[2].endian));
	out[3].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.we,
	&(out[3].nbc), &(out[3].nbl));
	out[3].img = mlx_get_data_addr(out[3].img, &(out[3].bpp),
	&(out[3].lsize), &(out[3].endian));
	out[4].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.s,
	&(out[4].nbc), &(out[4].nbl));
	out[4].img = mlx_get_data_addr(out[4].img, &(out[4].bpp),
	&(out[4].lsize), &(out[4].endian));
	return (out);
}
