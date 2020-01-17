/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:53:41 by augay             #+#    #+#             */
/*   Updated: 2020/01/17 16:53:42 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

typedef	struct	s_cub
{
	int			rw;
	int			rh;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			c;
	char		**map;
	int			mx;
	int			my;
	int			*sx;
	int			*sy;
}				t_cub;

typedef	struct	s_img
{
	void		*img;
	int			nbl;
	int			nbc;
	int			bpp;
	int			lsize;
	int			endian;
}				t_img;

typedef	struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_data;

typedef	struct	s_info
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			starto;
}				t_info;

typedef struct	s_wrap
{
	t_data		*data;
	t_info		*game;
	t_cub		*cub;
	t_img		*img;
	char		*out;
}				t_wrap;

typedef	struct	s_draw
{
	int			j;
	int			start;
	int			end;
	int			x;
}				t_draw;

#endif
