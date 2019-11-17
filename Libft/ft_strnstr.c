/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:43:23 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:43:24 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t		i;
	size_t		j;
	int			b;
	char		*out;

	out = (char*)hay;
	i = 0;
	if (!(j = 0) & (need[0] == '\0'))
		return (out);
	while ((b = 1) & (i < len && hay[i]))
	{
		if (hay[i] == need[j])
		{
			while (i + j++ < len && b)
			{
				if (need[j] != hay[i + j])
					b = 0;
				if (!(need[j]))
					return (out + i);
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
