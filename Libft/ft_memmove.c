/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:41:18 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:41:20 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	tmpstr[len];

	if (src == NULL)
		return (dst);
	i = 0;
	tmp = (unsigned char*)src;
	while (i < len)
	{
		tmpstr[i] = tmp[i];
		i++;
	}
	i = 0;
	tmp = dst;
	while (i < len)
	{
		tmp[i] = tmpstr[i];
		i++;
	}
	return (dst);
}
