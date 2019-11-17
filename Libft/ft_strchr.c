/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:42:42 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:42:43 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned long	i;
	char			*out;

	out = (char*)s;
	i = 0;
	while (out[i] || i == 0)
	{
		if ((char)c == s[i])
			return ((char*)s + i);
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char*)s + i);
	}
	return (NULL);
}
