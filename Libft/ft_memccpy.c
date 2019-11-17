/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:41:09 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:41:11 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp2;

	i = 0;
	if (dest == NULL)
		return (NULL);
	else if (n <= 0 || src == NULL)
		return (NULL);
	else
	{
		tmp = (unsigned char*)dest;
		tmp2 = (unsigned char*)src;
		while (i < n)
		{
			*tmp = *tmp2;
			if (*tmp2 == (unsigned char)c)
				return (dest + i + 1);
			tmp++;
			tmp2++;
			i++;
		}
		return (NULL);
	}
}
