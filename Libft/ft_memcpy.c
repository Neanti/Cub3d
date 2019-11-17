/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:41:02 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:41:04 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp2;

	i = 0;
	if (dest == NULL)
		return (NULL);
	else if (n <= 0 || src == NULL)
		return (dest);
	else
	{
		tmp = dest;
		tmp2 = (unsigned char*)src;
		while (i < n)
		{
			*tmp = *tmp2;
			tmp++;
			tmp2++;
			i++;
		}
		return (dest);
	}
}
