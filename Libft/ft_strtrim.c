/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:53:40 by augay             #+#    #+#             */
/*   Updated: 2019/10/09 11:53:43 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlength(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static char		*ft_substring(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*out;

	i = 0;
	while (s[i] && i < len)
		i++;
	if (i < start)
		return (NULL);
	if ((out = (char*)malloc(sizeof(char) * (i - start + 2))) == NULL)
		return (NULL);
	i = 0;
	while (i + start < len + 1 && s[i + start])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static int		checkend(char const *s1, char const *set, int i)
{
	int b;
	int j;
	int fin;

	b = 1;
	j = 0;
	fin = ft_strlength(s1);
	while (i > 0 && b)
	{
		b = 0;
		while (set[j] && !b)
		{
			if (set[j] == s1[i])
			{
				b = 1;
				fin--;
			}
			j++;
		}
		j = 0;
		i--;
	}
	return (fin);
}

int				checkstart(char const *s1, char const *set)
{
	int i;
	int b;
	int j;
	int start;

	i = 0;
	b = 1;
	start = 0;
	j = 0;
	while (s1[i] && b)
	{
		b = 0;
		while (set[j] && !b)
		{
			if (set[j] == s1[i])
			{
				b = 1;
				start++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (start);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		fin;
	char	*out;

	if (s1 == NULL || set == NULL)
		return ((s1 == NULL) ? NULL : ft_strdup(s1));
	fin = ft_strlength(s1);
	start = checkstart(s1, set);
	if (fin == start)
	{
		if ((out = (char*)malloc(sizeof(char))) == NULL)
			return (NULL);
		out[0] = '\0';
		return (out);
	}
	i = ft_strlength(s1) - 1;
	fin = checkend(s1, set, i);
	if (fin > 0)
	{
		return (ft_substring(s1, start, fin - 1));
	}
	return (NULL);
}
