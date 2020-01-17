#include "Libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "minilibx/mlx.h"
#include <sys/types.h>
#include <math.h>
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

int main(int ac, char **argv)
{
	if(begin_check(ac, argv) == 1)
		return (0);
	char *line;
	t_cub cub;
	int k = 0;
	int stat = 0;
	char *map;
	char *oldmap;
	map = malloc(sizeof(char));
	map[0] = '\0';
	char **rspl;
	int fd = open(argv[1], O_RDONLY);
	while ((k = get_next_line(fd, &line)) != 0)
	{
		if (stat == 0)
		{
			rspl = ft_split(line, ' ');
			fill_cub(rspl, &cub);
		}
		if (line[0] == '1')
		{
			oldmap = map;
			map = ft_strjoin(map, line);
			map = append_n(map);
			free(oldmap);
			stat = 1;
		}
		free(line);
	}
	free(line);
	if (try_path(&cub) == -1)
		return (er_path());
	if (cub.f == -1 || cub.c == -1)
		return (er_fc());
	int border = check_border(map);
	if (!border)
		return (er_map());
	char **g_map;
	g_map = ft_prepare_map(map, &cub.mx, &cub.my);
	cub.map = g_map;
	t_info game = prepare_info();
	locate_player(&game, &cub);
	locate_sprite(&cub);
	t_data data;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	int w = cub.rw;
	int h = cub.rh;
	t_img *txt = ft_prepare_txt(cub, data);
	t_wrap wrap;
	wrap.data = &data;
	wrap.game = &game;
	wrap.cub = &cub;
	wrap.img = txt;
	if (ac == 3)
	{
		char *out;
		out = prepare_out(w,h);
		wrap.out = out;
		s_fct_test(&wrap);
		int oo = open("save.bmp", O_WRONLY);
		write(oo, out, w * h * 4 + 54);
		close(oo);
		free(out);
		system("leaks a.out");
		exit(0);
	}
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w, h, "Cub3d")) == NULL)
		return (EXIT_FAILURE);
	mlx_key_hook(data.mlx_win, done, &wrap);
	fct_test(&wrap);
	close(fd);
	free(txt);
	free(g_map);
	system("leaks a.out");
	return (0);
}