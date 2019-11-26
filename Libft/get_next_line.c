/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:39:53 by augay             #+#    #+#             */
/*   Updated: 2019/10/28 16:41:46 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free(char *s1, char *s2)
{
	if (s1 != NULL)
	{
		free(s1);
	}
	if (s2 != NULL)
	{
		free(s2);
	}
	s2 = NULL;
	s1 = NULL;
	return (-1);
}

char	*ft_malloc(size_t size)
{
	char *out;

	out = malloc(size);
	out[0] = '\0';
	return (out);
}

char	*copy(char *s1)
{
	int		i;
	char	*out;

	i = 0;
	while (s1[i])
		i++;
	out = (char*)malloc(sizeof(char) * (i + 1));
	if (out == NULL)
		return (NULL);
	out[i] = '\0';
	i = 0;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	return (out);
}

int		ft_free_2(char **s, char **s2, int i, int t)
{
	if (i == 1)
	{
		if (*s != NULL)
			free(*s);
		*s = NULL;
		return (0);
	}
	else
	{
		if (s2 == NULL)
			return (-1);
		if (t == 0)
			return (-1);
		else if (!(s2[0] = malloc(sizeof(char) * 1)))
			return (-1);
		s2[0][0] = '\0';
		return (-1);
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*rest;
	ssize_t		t;
	char		*new;
	int			end;

	if ((!(t = BUFFER_SIZE) || t <= 0) || read(fd, NULL, 0) == -1)
		return (ft_free_2(NULL, line, 2, t));
	if (!(new = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || !line)
		return (ft_free_2(&new, NULL, 1, 1) - 1);
	if (!(new[t] = '\0') && rest == NULL)
		if ((rest = ft_malloc(sizeof(char))) == NULL)
			return (ft_free(new, line[0]));
	while (!contain(rest) && t == BUFFER_SIZE)
	{
		if ((t = lire(fd, new)) == -1)
			return (ft_free(new, NULL));
		rest = concat(rest, new, t);
	}
	ft_free(new, NULL);
	end = next(rest, line);
	if (end == 1 && ((rest = suppr(rest)) || 1))
		return (1);
	line[0] = copy(rest);
	ft_free_2(&rest, NULL, 1, 0);
	return (0);
}
