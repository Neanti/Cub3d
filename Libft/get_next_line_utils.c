/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:40:07 by augay             #+#    #+#             */
/*   Updated: 2019/10/16 09:40:09 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		contain(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

ssize_t	lire(int fd, char *s)
{
	ssize_t	r;
	int		i;

	i = 0;
	r = read(fd, s, BUFFER_SIZE);
	return (r);
}

char	*concat(char *s1, char *s2, ssize_t t)
{
	int		i;
	int		j;
	char	*out;

	j = 0;
	if (!(i = 0) && t < BUFFER_SIZE)
		s2[t] = '\0';
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	out = (char*)malloc(sizeof(char) * (j + i + 1));
	out[i + j] = '\0';
	i = 0;
	j = -1;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2[++j])
		out[i + j] = s2[j];
	free(s1);
	s1 = NULL;
	return (out);
}

int		next(char *rest, char **line)
{
	int i;

	if (contain(rest) == 0)
	{
		return (0);
	}
	i = 0;
	while (rest[i] != '\n' && rest[i])
		i++;
	line[0] = (char*)malloc(sizeof(char) * (i + 1));
	line[0][i] = '\0';
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		line[0][i] = rest[i];
		i++;
	}
	return (1);
}

char	*suppr(char *s)
{
	int		i;
	char	*out;
	int		k;

	i = 0;
	while (!(k = 0) && s[i] && s[i] != '\n')
		i++;
	while (s[i + k])
		k++;
	out = (char*)malloc(sizeof(char) * ((k == 0) ? 1 : k));
	out[(k == 0) ? 0 : k - 1] = '\0';
	if (k == 0)
	{
		free(s);
		return (out);
	}
	k = 0;
	i++;
	while (s[i - 1] && s[i + k])
	{
		out[k] = s[i + k];
		k++;
	}
	free(s);
	return (out);
}
