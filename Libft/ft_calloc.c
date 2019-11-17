/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:50:58 by augay             #+#    #+#             */
/*   Updated: 2019/10/15 12:13:23 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if ((ptr = malloc(count * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((char*)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
