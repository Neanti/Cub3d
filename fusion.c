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
// size_t strlcpy(char *dst, const char *src, size_t dsize)
// {
//	 const char *osrc = src;
//	 size_t nleft = dsize;

//	 /* Copy as many bytes as will fit. */
//	 if (nleft != 0) {
//		 while (--nleft != 0) {
//			 if ((*dst++ = *src++) == '\0')
//				 break;
//		 }
//	 }

//	 /* Not enough room in dst, add NUL and traverse rest of src. */
//	 if (nleft == 0) {
//		 if (dsize != 0)
//			 *dst = '\0';		/* NUL-terminate dst */
//		 while (*src++)
//			 ;
//	 }

//	 return(src - osrc - 1);	/* count does not include NUL */
// }

void print_cub(t_cub c)
{
	printf("---CUB---\nrw=%i, rh=%i, F=%i, C=%i, NO=%s, SO=%s, WE=%s, EA=%s, S=%s, mx=%i, my=%i\n---FIN---\n", c.rw, c.rh, c.F, c.C, c.NO, c.SO, c.WE, c.EA, c.S, c.mx, c.my);
}

void print_map(char **map)
{
	int i = 0;
	printf("---DEB MAP---\n");
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("---FIN MAP---\n");
}








int main(int ac, char **argv)
{
	if (ac == 1)
	{
		printf("Error\n Pas de fichier en argument\n");
		return (0);
	}
	if (check_ext(argv[1]) == 0)
	{
		printf("Error\n Extension fausse\n");
		return (0);
	}
	int fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
	{
		printf("Error\nEchec de read\n");
		return (0);
	}

	char *line;
	t_cub cub;
	int k = 0;
	int stat = 0;
	char *map;
	char *oldmap;

	map = malloc(sizeof(char));
	map[0] = '\0';
	printf("fd=%i\n", fd);
	while ((k = get_next_line(fd, &line)) != 0)
	{
		if (stat == 1 && ft_strtrim(line, " ")[0] != '1')
		{
			printf("Error\nMap coupé ou manque de mur\n");
			return (0);
		}
		if (stat == 0)
		{
			//printf("TOFILL line=%s\n", line);
			fill_cub(ft_split(line, ' '), &cub);
		}
		//printf("line=%s\n", line);
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
	//printf("line=%s\n", line);
	if (try_path(&cub) == -1)
	{
		printf("Error\nChemins non valides");
		return (0);
	}
	if (cub.F == -1 || cub.C == -1)
	{
		printf("Error\nMauvaises couleurs\n");
		return (0);
	}
	printf("---MAP---\n%s---FIN MAP---\n", map);
	int border = check_border(map);
	if (!border)
	{
		printf("Error\nManque de mur\n");
		return (0);
	}

	char **g_map;
	g_map = ft_prepare_map(map, &cub.mx, &cub.my);
	//printf("M01 %i %i\n", g_map[0][0], g_map[0][1]);
	print_cub(cub);
	cub.map = g_map;
	t_info game = prepare_info();
	locate_player(&game, &cub);
	print_map(g_map);
	locate_sprite(&cub);
	//printf("x1=%i,y1=%i,x2=%i,y2=%i\n",cub.sx[0],cub.sy[0],cub.sx[1],cub.sy[1]);
	//fin parsing debut jeu
	data_t data;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	int w = cub.rw;
	int h = cub.rh;
	t_img *txt = ft_prepare_txt(cub, data);
	if (ac == 3)
	{
		printf("save img\n");
		char *out;
		out = prepare_out(w,h);
		save_fct_test(&game, &cub, txt, out);
		int oo = open("save.bmp", O_WRONLY);
		write(oo, out, w * h * 4 + 54);
		close(oo);
		exit(0);
	}
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w, h, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	//game.w = w;
	//game.h = h;
	t_wrap wrap;
	wrap.data = &data;
	wrap.game = &game;
	wrap.cub = &cub;
	wrap.img = txt;
	mlx_key_hook(data.mlx_win, done, &wrap);
	//mlx_hook()
	fct_test(data, -1, &game, &cub, txt);
	close(fd);
	free(txt);
	free(g_map);
	system("leaks a.out");
	return (0);
}