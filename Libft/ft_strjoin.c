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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*out;

	l = 0;
	if (!(i = 0) && s1 == NULL)
		return ((s2 == NULL) ? NULL : ft_strdup(s2));
	if (s2 == NULL)
		return ((s1 == NULL) ? NULL : ft_strdup(s1));
	while (!(j = 0) && s1[i])
		i++;
	while ((k = -1) && s2[j])
		j++;
	if ((out = (char*)malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	out[i + j] = '\0';
	while (++k < i)
		out[k] = s1[k];
	while (k < i + j)
		out[k++] = s2[l++];
	return (out);
}
