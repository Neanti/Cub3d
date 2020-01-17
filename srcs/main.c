/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:28:19 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 14:28:20 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	save_image(t_wrap *wrap)
{
	char	*out;
	int		fd;

	out = prepare_out(wrap->cub->rw, wrap->cub->rh);
	wrap->out = out;
	s_fct_test(wrap);
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC);
	write(fd, out, wrap->cub->rw * wrap->cub->rh * 4 + 54);
	close(fd);
	free(out);
	exit(0);
}

int		check_cub_start(char *map, t_cub cub)
{
	int border;

	if (try_path(&cub) == -1)
		exit(er_path());
	if (cub.f == -1 || cub.c == -1)
		exit(er_fc());
	border = check_border(map);
	if (!border)
		exit(er_map());
	return (0);
}

char	*wrap_join(char *s, char *s2)
{
	char *old;

	old = s;
	s = ft_strjoin(s, s2);
	free(old);
	s = append_n(s);
	return (s);
}

void	gnl_use(char *s, t_cub *cub)
{
	int		fd;
	char	*line;
	int		k;
	char	*map;
	int		stat;

	fd = open(s, O_RDONLY);
	stat = 0;
	k = 1;
	if ((map = malloc(sizeof(char))) == NULL)
		exit(er_mem());
	map[0] = '\0';
	while ((k == 1) && (k = get_next_line(fd, &line)) >= 0)
	{
		if (stat == 0)
			fill_cub(ft_split(line, ' '), cub);
		if (line[0] == '1' && (stat = 1))
			map = wrap_join(map, line);
		free(line);
	}
	close(fd);
	check_cub_start(map, *cub);
	cub->map = ft_prepare_map(map, &cub->mx, &cub->my);
}

int		main(int ac, char **argv)
{
	t_wrap	*wrap;
	t_cub	cub;
	t_info	game;
	t_img	*txt;
	t_data	data;

	if (begin_check(ac, argv) == 1)
		return (0);
	gnl_use(argv[1], &cub);
	game = prepare_info();
	locate_player(&game, &cub);
	locate_sprite(&cub);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	txt = ft_prepare_txt(cub, data);
	wrap = init_wrap(&data, &game, &cub, txt);
	if (ac == 3)
		save_image(wrap);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, cub.rw,
	cub.rh, "Cub3d")) == NULL)
		return (0);
	mlx_key_hook(data.mlx_win, done, wrap);
	mlx_hook(data.mlx_win, 17, 0, handle_quit, wrap);
	fct_test(wrap);
	return (0);
}
