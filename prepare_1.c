/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:35:14 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:35:15 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_ext(char *s)
{
	int l;

	if (s == NULL)
		return (0);
	l = ft_strlen(s);
	if (l < 5)
		return (0);
	if (s[--l] != 'b')
	{
		return (0);
	}
	if (s[--l] != 'u')
		return (0);
	if (s[--l] != 'c')
		return (0);
	if (s[--l] != '.')
		return (0);
	return (1);
}

int		arrange(char **s)
{
	char	**sp;
	int		color;
	char	*s2;
	int		i[3];

	s2 = fusion(s + 1);
	color = -1;
	sp = ft_split(s2, ',');
	if (sp[0] && sp[1] && sp[2] && !sp[3])
	{
		i[0] = ft_check_int(sp[0]) ? ft_atoi(sp[0]) : -1;
		i[1] = ft_check_int(sp[1]) ? ft_atoi(sp[1]) : -1;
		i[2] = ft_check_int(sp[2]) ? ft_atoi(sp[2]) : -1;
		if (i[0] == -1 || i[1] == -1 || i[2] == -1)
			return (-1);
		color = get_color(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
	}
	int j = 0;
	while(sp[j])
		free(sp[j++]);
	free(sp);
	return (color);
}

int		check_id(char *s)
{
	if (!ft_strncmp(s, "R", 10))
		return (1);
	else if (!ft_strncmp(s, "NO", 10))
		return (2);
	else if (!ft_strncmp(s, "SO", 10))
		return (3);
	else if (!ft_strncmp(s, "WE", 10))
		return (4);
	else if (!ft_strncmp(s, "EA", 10))
		return (5);
	else if (!ft_strncmp(s, "S", 10))
		return (6);
	else if (!ft_strncmp(s, "F", 10))
		return (7);
	else if (!ft_strncmp(s, "C", 10))
		return (8);
	else
		return (-1);
}

void	check_cub(t_cub *cub, char **s, int id)
{
	if (id == 2)
		cub->NO = ft_strdup(s[1]);
	else if (id == 3)
		cub->SO = ft_strdup(s[1]);
	else if (id == 4)
		cub->WE = ft_strdup(s[1]);
	else if (id == 5)
		cub->EA = ft_strdup(s[1]);
	else if (id == 6)
		cub->S = ft_strdup(s[1]);
	else if (id == 7)
		cub->F = arrange(s);
	else if (id == 8)
		cub->C = arrange(s);
}

void	fill_cub(char **s, t_cub *cub)
{
	int i;
	int id;

	if (s[0] != 0)
		id = check_id(s[0]);
	else
		return ;
	if (s[1] == 0)
		return ;
	if (id == 1)
	{
		cub->rw = ft_atoi(s[1]);
		cub->rh = ft_atoi(s[2]);
	}
	else
	{
		check_cub(cub, s, id);
	}
	i = 0;
	while(s[i])
		free(s[i++]);
	//free(s);
}
