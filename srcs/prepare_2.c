/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:37:32 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:37:33 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		try_fd(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (-1);
	}
	if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int		try_path(t_cub *cub)
{
	if (try_fd(cub->no) < 0)
		return (-1);
	if (try_fd(cub->so) < 0)
		return (-1);
	if (try_fd(cub->we) < 0)
		return (-1);
	if (try_fd(cub->ea) < 0)
		return (-1);
	if (try_fd(cub->s) < 0)
		return (-1);
	return (1);
}

char	*append_n(char *s)
{
	char	*out;
	int		i;

	i = 0;
	if ((out = malloc(sizeof(char) * (ft_strlen(s) + 2))) == NULL)
		return (NULL);
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\n';
	out[++i] = '\0';
	free(s);
	return (out);
}

int		is_in_map(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' ||
	c == 'E' || c == 'W' || c == '\n' || c == ' ')
		return (1);
	else if (c == '1')
		return (2);
	else
		return (0);
}

int		is_closed(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n')
	{
		if (!(s[i] == '1' || s[1] == ' '))
			return (0);
		i++;
	}
	i = ft_strlen(s) - 2;
	while (s[i] != '\n')
	{
		if (!(s[i] == '1' || s[1] == ' '))
			return (0);
		i--;
	}
	i = 0;
	while (s[i++])
		if (s[i] == '\n' && s[i + 1])
		{
			if (s[i - 1] != '1' || s[i + 1] != '1')
				return (0);
		}
	return (1);
}
