/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:22:44 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 12:22:45 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*add_char(char *s, int n)
{
	char	*out;
	int		l;
	int		i;

	l = (int)strlen(s);
	out = s;
	out[l + 1] = '\0';
	i = 0;
	while (i < l)
	{
		i++;
	}
	out[i] = n + 48;
	return (out);
}

int		check_border(char *s)
{
	int	i;
	int	player;

	player = 0;
	i = 0;
	while (s[i])
	{
		if (!is_in_map(s[i]))
			return (0);
		i++;
	}
	if (!is_closed(s))
	{
		return (0);
	}
	return (1);
}

t_draw	*ft_pack(int a, int b, int c, int d)
{
	t_draw *draw;

	draw = malloc(sizeof(t_draw));
	draw->j = d;
	draw->start = b;
	draw->end = c;
	draw->x = a;
	return (draw);
}
