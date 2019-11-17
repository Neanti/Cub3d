/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:43:28 by augay             #+#    #+#             */
/*   Updated: 2019/10/10 13:43:29 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start(const char *str, int *i, int *j)
{
	while (str[*i] && *j == 0)
	{
		if (str[*i] == '\t' || str[*i] == ' ' || str[*i] == '\f' ||
		str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\v')
			(*i)++;
		else if (str[*i] == '-')
		{
			(*i)++;
			(*j)--;
		}
		else if (str[*i] == '+')
		{
			(*i)++;
			(*j)++;
		}
		else if (str[*i] >= 48 && str[*i] <= 57)
			(*j)++;
		else
			return (0);
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int i;
	int j;
	int res;

	i = 0;
	j = 0;
	res = 0;
	if (start(str, &i, &j) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			res = res * 10 + (str[i] - 48);
		else
			return (res * j);
		i++;
	}
	return (res * j);
}
