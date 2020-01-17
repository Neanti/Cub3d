#include "cub.h"


int check_save(char *s)
{
	if(s[0] && s[0] != '-')
		return (0);
	if(s[1] && s[1] != 's')
		return (0);
	if(s[2] && s[2] != 'a')
		return (0);
	if(s[3] && s[3] != 'v')
		return (0);
	if(s[4] && s[4] != 'e')
		return (0);
	if (s[5] != '\0')
		return (0);
	return (1);
}

int	begin_check(int ac, char **argv)
{
	if (ac == 1)
		return (er_file());
	if (check_ext(argv[1]) == 0)
		return (er_ext());
	int fd = open(argv[1], O_RDONLY);
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

void save_image(t_wrap *wrap)
{
		char *out;
		int fd;

		out = prepare_out(wrap->cub->rw,wrap->cub->rh);
		wrap->out = out;
		s_fct_test(wrap);
		fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC);
		write(fd, out, wrap->cub->rw * wrap->cub->rh * 4 + 54);
		close(fd);
		free(out);
		exit(0);
}

int check_cub_start(char *map, t_cub cub)
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

char *wrap_join(char *s, char *s2)
{
	char *old;

	old = s;
	s = ft_strjoin(s, s2);
	free(old);
	return (s);
}

void gnl_use(char *s, t_cub *cub)
{
	int fd;
	char *line;
	int k;
	char *map;
	int stat;

	fd = open(s, O_RDONLY);
	stat = 0;
	k = 1;
	map = malloc(sizeof(char));
	map[0] = '\0';
	while ((k == 1) && (k = get_next_line(fd, &line)) >= 0)
	{
		if (stat == 0)
			fill_cub(ft_split(line, ' '), cub);
		if (line[0] == '1')
		{
			map = wrap_join(map, line);
			map = append_n(map);
			stat = 1;
		}
		free(line);
	}
	close(fd);
	check_cub_start(map, *cub);
	cub->map = ft_prepare_map(map, &cub->mx, &cub->my);
}

int main(int ac, char **argv)
{
	t_wrap	wrap;
	t_cub	cub;
	t_info	game;
	t_img	*txt;
	t_data	data;

	if(begin_check(ac, argv) == 1)
		return (0);
	gnl_use(argv[1], &cub);
	game = prepare_info();
	locate_player(&game, &cub);
	locate_sprite(&cub);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	txt = ft_prepare_txt(cub, data);
	wrap.data = &data;
	wrap.game = &game;
	wrap.cub = &cub;
	wrap.img = txt;
	if (ac == 3)
		save_image(&wrap);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, cub.rw, cub.rh, "Cub3d")) == NULL)
		return (0);
	mlx_key_hook(data.mlx_win, done, &wrap);
	fct_test(&wrap);
	return (0);
}
