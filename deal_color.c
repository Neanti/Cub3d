/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:26:52 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:26:53 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_color(int r, int g, int b)
{
	int o;

	o = 0;
	o = r;
	o = o << 8;
	o = o + g;
	o = o << 8;
	o = o + b;
	return (o);
}

int	deal_pack(char *s)
{
	int	i;
	int	k;
	int	b;
	int	so;

	i = 0;
	k = 8;
	b = 128;
	so = 0;
	while (i < k)
	{
		so = so + b * (s[i] - 48);
		b = b / 2;
		i++;
	}
	return (so);
}

int	bin2col(char *s, int endian)
{
	int		i;
	char	*out;
	int		c;
	int		t[3];

	i = 0;
	out = s;
	t[0] = deal_pack(out);
	t[1] = deal_pack(out + 8);
	t[2] = deal_pack(out + 16);
	if (endian == 0)
		c = get_color(t[2], t[1], t[0]);
	else
	{
		c = get_color(t[0], t[1], t[2]);
	}
	return (c);
}

int	pick_color(t_img img, int x, int y)
{
	char	*res;
	int		k;
	int		l;
	char	*s;
	int		color;

	if ((res = malloc(sizeof(char) * (img.bpp + 1))) == NULL)
		return (-10);
	res[0] = '\0';
	k = (x - 1) * img.nbc * (img.bpp / 8) + (y - 1) * (img.bpp / 8);
	x = 0;
	l = 0;
	s = img.img;
	while (x < img.bpp)
	{
		res = add_char(res, !!((s[k] << l) & 0x80));
		x++;
		l++;
		if (x % 8 == 0 && !(l = 0))
			k++;
	}
	color = (res[img.bpp - 1] == '1') ? -1 : bin2col(res, img.endian);
	free(res);
	return (color);
}

int	ft_check_int(char *s)
{
	int		i;
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	i = 0;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	i = ft_atoi(tmp);
	if (i > 255 || i < 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}
