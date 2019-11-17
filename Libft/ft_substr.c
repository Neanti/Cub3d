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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*out;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < len + start)
		i++;
	if (i < start)
	{
		if ((out = (char*)malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		out[0] = '\0';
		return (out);
	}
	if ((out = (char*)malloc(sizeof(char) * (i - start + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i + start < len + start && s[i + start])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}
