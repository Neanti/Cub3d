/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:29:07 by augay             #+#    #+#             */
/*   Updated: 2020/01/14 10:29:09 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB_H
# define FT_CUB_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include "minilibx/mlx.h"
# include <sys/types.h>
# include <math.h>

typedef struct	s_cub
{
	int		rw;
	int		rh;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
	int		F;
	int		C;
	char	**map;
	int		mx;
	int		my;
	int		*sx;
	int		*sy;
}				t_cub;

typedef struct	s_img
{
	void	*img;
	int		nbl;
	int		nbc;
	int		bpp;
	int		lsize;
	int		endian;
}				t_img;

typedef struct	data_s
{
	void *mlx_ptr;
	void *mlx_win;
}				data_t;

typedef struct	s_info
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	int		startO;
	//int h;
	//int w;
}				t_info;

typedef struct	s_wrap
{
	data_t	*data;
	t_info	*game;
	t_cub	*cub;
	t_img	*img;
}				t_wrap;

int get_color(int r, int g, int b);
int deal_pack(char *s);
int bin2col(char *s, int endian);
int pick_color(t_img img, int x, int y);
int ft_check_int(char *s);
int check_ext(char *s);
int arrange(char **s);
int check_id(char *s);
void fill_cub(char **s, t_cub *cub);
char *add_char(char *s, int n);
int try_fd(char *s);
int try_path(t_cub *cub);
char *append_n(char *s);
int is_in_map(char c);
int is_closed(char *s);
int check_border(char *s);
t_info prepare_info(void);
char **remove_space(char **s, int *x, int *y);
void locate_player(t_info *game, t_cub *cub);
void locate_sprite(t_cub *cub);
void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt);
void save_fct_test(t_info *game, t_cub *cub, t_img *txt, char *out);
void	save_pixel_put(int stripe, int y, int color, char *out, t_cub *cub);
char *prepare_out(int w, int h);
void save_ft_put_line(int x, int start, int end, t_img *txt, int j, int nbt, double wallX, char *out, t_cub *cub);
void ft_put_int(int n, char **s, int of);
t_img *ft_prepare_txt(t_cub cub, data_t data);
void	sort_sprite(t_cub *cub, double posX, double posY);
double dist(double posX, double posY, int sx, int sy);
double ft_calc_vec(double x, double y, double rX, double rY);
void rot_vec(double a, t_info *game);
double d2r(double d);
void ft_split_free(char **s);
char *fusion(char **s);
void ft_put_line(int x, int start, int end, t_img *txt, data_t data, int j, int nbt, double wallX, t_cub *cub);
char **ft_prepare_map(char *m, int *x, int *y);
int done(int key, void *a);
int count_sprite(char **s);

#endif