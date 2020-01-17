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
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <sys/types.h>
# include <math.h>
# include "cub_struct.h"

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
void	s_fct_test(t_wrap *wrap);
void	s_pixel_put(t_draw *draw, char *out, t_cub *cub);
char	*prepare_out(int w, int h);
void	s_put_line(t_draw *draw, int nbt, double wall_x, t_wrap *wrap);
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
t_draw	*ft_pack(int x, int start, int end, int j);
int		nbt(int side, double raydir_x, double raydir_y);
double	find_wallx(int side, t_wrap *wrap, double wall_dist, int x);
double	*de(t_wrap *wrap, double zbuffer[wrap->cub->rw], int t[7], double d[7]);
int		deal_side(double *sdist, double ddist, int *map, int step);
double	calc_wall(int map, double pos, int step, double raydir);
void	prep_no(t_wrap *wrap, int t[7]);
void	prep_nod(t_wrap *wrap, double d[7], int x, int t[7]);
double	*deal_wall(t_wrap *wrap, int x, double zbuffer[wrap->cub->rw]);
void	prep_spd(t_wrap *wrap, double d[2], int i, int t[14]);
int		er_file(void);
int		er_ext(void);
int		er_read(void);
int		er_fc(void);
int		er_path(void);
int		er_map(void);
int		er_arg(void);
int		er_save(void);
int		check_save(char *s);
int		begin_check(int ac, char **argv);
t_wrap	*init_wrap(t_data *data, t_info *game, t_cub *cub, t_img *txt);
int		handle_quit(void *param);
int		er_mem(void);

#endif
