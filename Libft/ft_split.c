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

static char	**splitbody(int nbc, char const *s, char c, char **out)
{
	int i;
	int j;
	int k;

	k = 0;
	if (!(i = 0) && s[0] != c)
	{
		while (s[i] && s[i] != c)
			i++;
		out[k] = ft_substr(s, 0, i);
		k++;
	}
	while (!(j = 0) && s[i] && k < nbc)
	{
		if ((i == 0 || s[i] == c))
			if (s[i + 1] != c)
			{
				while (s[i + 1 + j] && s[i + 1 + j] != c)
					j++;
				out[k] = ft_substr(s, i + 1, j);
				k++;
			}
		i++;
	}
	return (out);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		nbc;
	char	**out;

	if (s == NULL)
		return (NULL);
	i = 0;
	nbc = 0;
	if (s[0] && s[0] != c)
		nbc++;
	while (s[i] && s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			nbc++;
		i++;
	}
	if ((out = (char**)malloc(sizeof(char*) * (nbc + 1))) == NULL)
		return (NULL);
	if ((out[nbc] = (char*)malloc(sizeof(char))) == NULL)
		return (NULL);
	out[nbc] = 0;
	if (nbc > 0)
		return (splitbody(nbc, s, c, out));
	return (out);
}
