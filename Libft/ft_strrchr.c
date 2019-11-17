/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:42:52 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:42:53 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		n;

	n = -1;
	i = 0;
	while (s[i] || i == 0)
	{
		if ((char)c == s[i])
			n = i;
		i++;
	}
	if ((char)c == '\0' && s[0] != '\0')
		return ((char*)s + i);
	if (n == -1)
		return (NULL);
	else
		return ((char*)s + n);
}
