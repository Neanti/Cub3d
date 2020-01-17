/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:41:45 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 14:41:46 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_save(char *s)
{
	if (s[0] && s[0] != '-')
		return (0);
	if (s[1] && s[1] != 's')
		return (0);
	if (s[2] && s[2] != 'a')
		return (0);
	if (s[3] && s[3] != 'v')
		return (0);
	if (s[4] && s[4] != 'e')
		return (0);
	if (s[5] != '\0')
		return (0);
	return (1);
}

int		begin_check(int ac, char **argv)
{
	int fd;

	if (ac == 1)
		return (er_file());
	if (check_ext(argv[1]) == 0)
		return (er_ext());
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (er_read());
	if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		return (er_read());
	}
	close(fd);
	if (ac > 3)
		return (er_arg());
	if (ac == 3 && check_save(argv[2]) == 0)
		return (er_save());
	return (0);
}

t_wrap	*init_wrap(t_data *data, t_info *game, t_cub *cub, t_img *txt)
{
	t_wrap *wrap;

	if ((wrap = malloc(sizeof(t_wrap))) == NULL)
		exit(er_mem());
	wrap->data = data;
	wrap->game = game;
	wrap->cub = cub;
	wrap->img = txt;
	return (wrap);
}

int		handle_quit(void *param)
{
	t_wrap *w;

	w = param;
	mlx_destroy_window(w->data->mlx_ptr, w->data->mlx_win);
	exit(0);
}
