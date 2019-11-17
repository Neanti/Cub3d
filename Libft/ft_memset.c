/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:40:41 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:40:44 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	if (len <= 0)
		return (b);
	else
	{
		tmp = b;
		while (i < len)
		{
			*tmp = c;
			tmp++;
			i++;
		}
		return (b);
	}
}
