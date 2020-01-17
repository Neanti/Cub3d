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

#ifndef CUB_H
# define CUB_H

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

typedef	struct	s_cub
{
	int		rw;
	int		rh;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;
	char	**map;
	int		mx;
	int		my;
	int		*sx;
	int		*sy;
}				t_cub;

typedef	struct	s_img
{
	void	*img;
	int		nbl;
	int		nbc;
	int		bpp;
	int		lsize;
	int		endian;
}				t_img;

typedef	struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_data;

typedef	struct	s_info
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	int		starto;
}				t_info;

typedef struct	s_wrap
{
	t_data	*data;
	t_info	*game;
	t_cub	*cub;
	t_img	*img;
}				t_wrap;

typedef	struct	s_draw
{
	int		j;
	int		start;
	int		end;
	int		x;
}				t_draw;

int		get_color(int r, int g, int b);
int		deal_pack(char *s);
int		bin2col(char *s, int endian);
int		pick_color(t_img img, int x, int y);
int		ft_check_int(char *s);
int		check_ext(char *s);
int		arrange(char **s);
int		check_id(char *s);
void	fill_cub(char **s, t_cub *cub);
char	*add_char(char *s, int n);
int		try_fd(char *s);
int		try_path(t_cub *cub);
char	*append_n(char *s);
int		is_in_map(char c);
int		is_closed(char *s);
int		check_border(char *s);
t_info	prepare_info(void);
char	**remove_space(char **s, int *x, int *y);
void	locate_player(t_info *game, t_cub *cub);
void	locate_sprite(t_cub *cub);
void	fct_test(t_wrap *wrap);
void	save_fct_test(t_info *game, t_cub *cub, t_img *txt, char *out);
void	save_pixel_put(t_draw *draw, char *out, t_cub *cub);
char	*prepare_out(int w, int h);
void	save_ft_put_line(int x, int start, int end, t_img *txt, int j, int nbt, double wallx, char *out, t_cub *cub);
void	ft_put_int(int n, char **s, int of);
t_img	*ft_prepare_txt(t_cub cub, t_data data);
void	sort_sprite(t_cub *cub, double posx, double posy);
double	dist(double posx, double posy, int sx, int sy);
double	ft_calc_vec(double x, double y, double rx, double ry);
void	rot_vec(double a, t_info *game);
double	d2r(double d);
void	ft_split_free(char **s);
char	*fusion(char **s);
void	ft_put_line(t_draw *draw, int nbt, double wallx, t_wrap *wrap);
char	**ft_prepare_map(char *m, int *x, int *y);
int		done(int key, void *a);
int		count_sprite(char **s);
t_draw	*ft_pack(int , int start, int end, int j);
int		nbt(int side, double raydir_x, double raydir_y);
double	find_wallx(int side, t_wrap *wrap, double wall_dist, int x);
double	*de(t_wrap *wrap, double zbuffer[wrap->cub->rw], int t[7], double d[7]);
int		deal_side(double *sdist, double ddist, int *map, int step);
double	calc_wall(int map, double pos, int step, double raydir);
void	prep_no(t_wrap *wrap, int t[7]);
void	prep_nod(t_wrap *wrap, double d[7], int x, int t[7]);
double	*deal_wall(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw]);

#endif
