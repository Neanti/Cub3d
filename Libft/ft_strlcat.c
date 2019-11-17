/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:43:16 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:43:18 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	out;
	size_t	tmp;

	out = 0;
	while (dst[out] && out < size)
		out++;
	out = (out < size) ? out : size;
	tmp = 0;
	while (src[tmp])
		tmp++;
	out = out + tmp;
	if (out - tmp > size)
		return (out);
	i = 0;
	j = 0;
	while (dst[i] && i < size && size != 0)
		i++;
	while (i < size - 1 && size != 0 && src[j])
		dst[i++] = src[j++];
	while (i < size)
		dst[i++] = '\0';
	return (out);
}
