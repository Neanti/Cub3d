/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:38:23 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 13:38:24 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int er_map()
{
	ft_putstr_fd("Error\nLa carte n'est pas valide.\n", 2);
	return (1);
}

int er_arg()
{
	ft_putstr_fd("Error\nIl y a trop d'arguments.\n", 2);
	return (1);
}

int er_save()
{
	ft_putstr_fd("Error\nLe second argument n'est pas reconnu.\n", 2);
	return (1);
}
