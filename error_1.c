/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:38:17 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 13:38:18 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	er_file(void)
{
	ft_putstr_fd("Error\nPas de fichier en argument.\n", 2);
	return (1);
}

int	er_ext(void)
{
	ft_putstr_fd("Error\nLe fichier n'as pas la bonne extension.\n", 2);
	return (1);
}

int	er_read(void)
{
	ft_putstr_fd("Error\nLa lecture n'as pas fonctionné.\n", 2);
	return (1);
}

int	er_fc(void)
{
	ft_putstr_fd("Error\nLe champ C ou F est incorrect.\n", 2);
	return (1);
}

int	er_path(void)
{
	ft_putstr_fd("Error\nAu moins un des chemins n'est pas valide.\n", 2);
	return (1);
}
