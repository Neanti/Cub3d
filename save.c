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
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
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

int get_color(int r, int g, int b)
{
	int o;

	o = 0;
	o = r;
	o = o << 8;
	o = o + g;
	o = o << 8;
	o = o + b;
	return (o);
}

void print_cub(t_cub c)
{
	////printf("---CUB---\nrw=%i, rh=%i, F=%i, C=%i, NO=%s, SO=%s, WE=%s, EA=%s, S=%s, mx=%i, my=%i\n---FIN---\n", c.rw, c.rh, c.F, c.C, c.NO, c.SO, c.WE, c.EA, c.S, c.mx, c.my);
}

int check_ext(char *s)
{
	int l;

	if (s == NULL)
		return (0);
	l = ft_strlen(s);
	if (l < 5)
		return (0);
	if (s[--l] != 'b')
	{
		return (0);
	}
	if (s[--l] != 'u')
		return (0);
	if (s[--l] != 'c')
		return (0);
	if (s[--l] != '.')
		return (0);
	return (1);
}

void ft_split_free(char **s)
{
	while (s[0] != 0)
	{
		free(s[0]);
		s = s + 1;
	}
	free(s[0]);
	//free(s);
}

int ft_check_int(char *s)
{
	int		i;
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	i = 0;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	i = ft_atoi(tmp);
	if (i > 255 || i < 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

char *fusion(char **s)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 1;
	s1 = s[0];
	while (s[i])
	{
		s2 = s1;
		s1 = ft_strjoin(s1, s[i]);
		free(s2);
		i++;
	}
	return (s1);
}

int arrange(char **s)
{
	char	**sp;
	int		color;
	int		i1;
	int		i2;
	int		i3;
	char	*s2;

	s2 = fusion(s + 1);
	color = -1;
	sp = ft_split(s2, ',');
	if (sp[0] && sp[1] && sp[2] && !sp[3])
	{
		i1 = ft_check_int(sp[0]) ? ft_atoi(sp[0]) : -1;
		i2 = ft_check_int(sp[1]) ? ft_atoi(sp[1]) : -1;
		i3 = ft_check_int(sp[2]) ? ft_atoi(sp[2]) : -1;
		if (i1 == -1 || i2 == -1 || i3 == -1)
			return (-1);
		color = get_color(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
	}
	return (color);
}

int check_id(char *s)
{
	//////printf("checkid de %s\n\n",s);
	if (!ft_strncmp(s, "R", 10))
	{
		return (1);
	}
	else if (!ft_strncmp(s, "NO", 10))
	{
		return (2);
	}
	else if (!ft_strncmp(s, "SO", 10))
	{
		return (3);
	}
	else if (!ft_strncmp(s, "WE", 10))
	{
		return (4);
	}
	else if (!ft_strncmp(s, "EA", 10))
	{
		return (5);
	}
	else if (!ft_strncmp(s, "S", 10))
	{
		return (6);
	}
	else if (!ft_strncmp(s, "F", 10))
	{
		return (7);
	}
	else if (!ft_strncmp(s, "C", 10))
	{
		return (8);
	}
	else
		return (-1);
}

void ft_put_int(int n, char **s, int of);


void fill_cub(char **s, t_cub *cub)
{
	int i;
	int id;

	if (s[0] != 0)
		id = check_id(s[0]);
	else
		return;
	if (s[1] == 0)
		return;
	if (id == 1)
	{
		cub->rw = ft_atoi(s[1]);
		cub->rh = ft_atoi(s[2]);
	}
	else if (id == 2)
	{
		cub->NO = ft_strdup(s[1]);
	}
	else if (id == 3)
	{
		cub->SO = ft_strdup(s[1]);
	}
	else if (id == 4)
	{
		cub->WE = ft_strdup(s[1]);
	}
	else if (id == 5)
	{
		cub->EA = ft_strdup(s[1]);
	}
	else if (id == 6)
	{
		cub->S = ft_strdup(s[1]);
	}
	else if (id == 7)
	{
		cub->F = arrange(s);
	}
	else if (id == 8)
	{
		cub->C = arrange(s);
	}

	//ft_split_free(s);
}

char *swap(char *s)
{
	int		i;
	int		l;
	int		k;
	char	c;
	int		n;

	i = 0;
	l = ft_strlen(s);
	k = 7;
	n = 0;
	//////printf("\nORIG=%s\n",s);
	while (k != l - 1)
	{

		//////printf("i=%i, k=%i, l=%i\n",i,k,l);
		while (i < k)
		{
			//////printf("\t\ti=%i, k=%i\n",i,k);
			c = s[i];
			s[i] = s[k];
			s[k] = c;
			i++;
			k--;
		}
		n++;
		i = 8 * n;
		k = 8 * n + 7;
	}
	//////printf("SWAP=%s\n",s);
	return (s);
}

int deal_pack(char *s)
{
	int	i;
	int	k;
	int	b;
	int	so;

	i = 0;
	k = 8;
	b = 128;
	so = 0;
	while (i < k)
	{
		so = so + b * (s[i] - 48);
		b = b / 2;
		i++;
	}
	//////printf("PAR=%d\n",so);
	return (so);
}

int bin2col(char *s, int endian)
{
	int		i;
	char	*out;
	int		c;
	int		t[3];

	i = 0;
	// if (endian == 0)
	// 	out = swap(s);
	// else
	// {
	// 	out = s;
	// }
	out = s;
	t[0] = deal_pack(out);
	t[1] = deal_pack(out + 8);
	t[2] = deal_pack(out + 16);
	if (endian == 0)
		c = get_color(t[2], t[1], t[0]);
	else
	{
		c = get_color(t[0], t[1], t[2]);
	}

	return (c);
}

char *add_char(char *s, int n)
{
	char	*out;
	int		l;
	int		i;

	l = (int)strlen(s);
	out = s;
	out[l + 1] = '\0';
	i = 0;
	while (i < l)
	{
		i++;
	}
	out[i] = n + 48;
	//free(s);
	return (out);
}

int pick_color(t_img img, int x, int y)
{
	// ////printf("PICK x=%i y=%i\n",x,y);
	int		i;
	char	*res;
	int		k;
	int		l;
	char	*s;
	int		color;
	//res = malloc(sizeof(char) * 1);
	res = malloc(sizeof(char) * (img.bpp + 1));
	res[0] = '\0';
	k = (x - 1) * img.nbc * (img.bpp / 8) + (y - 1) * (img.bpp / 8);
	//////printf("%s\n",s);
	i = 0;
	//int k = 0;
	l = 0;
	s = img.img;
	//////printf("k=%i\n",k);
	while (i < img.bpp)
	{
		//////printf("\n\nk=%i, i%i\n\n", k,i);
		//////printf("%d", !!((s[k] << l) & 0x80));
		res = add_char(res, !!((s[k] << l) & 0x80));
		i++;
		l++;
		if (i % 8 == 0)
		{
			//////printf(".");
			k++;
			l = 0;
		}
	}
	color = bin2col(res, img.endian);
	//////printf("RES=%s\n",res);
	if (res[img.bpp - 1] == '1')
		color = -1;
	//////printf("END et RES=%s\n",res);
	return (color);
}

int try_fd(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (-1);
	}
	if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int try_path(t_cub *cub)
{
	if (try_fd(cub->NO) < 0)
		return (-1);
	if (try_fd(cub->SO) < 0)
		return (-1);
	if (try_fd(cub->WE) < 0)
		return (-1);
	if (try_fd(cub->EA) < 0)
		return (-1);
	if (try_fd(cub->S) < 0)
		return (-1);
	return (1);
}

char *append_n(char *s)
{
	char	*out;
	int		i;

	i = 0;
	out = malloc(sizeof(char) * (ft_strlen(s) + 2));
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\n';
	out[++i] = '\0';
	free(s);
	return (out);
}

int is_in_map(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '\n' || c == ' ')
		return (1);
	else if (c == '1')
		return (2);
	else
		return (0);
}

int is_closed(char *s)
{
	int	i;

	i = 0;
	////printf("1st part border\n");
	while (s[i] != '\n')
	{
		if (!(s[i] == '1' || s[1] == ' '))
			return (0);
		i++;
	}
	i = ft_strlen(s) - 2;
	while (s[i] != '\n')
	{
		if (!(s[i] == '1' || s[1] == ' '))
			return (0);
		i--;
	}
	////printf("2nd part border\n");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n' && s[i + 1])
		{
			if (s[i - 1] != '1' || s[i + 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int check_border(char *s)
{
	int	i;
	int	player;

	player = 0;
	i = 0;
	while (s[i])
	{
		if (!is_in_map(s[i]))
			return (0);
		i++;
	}
	////printf("2nd part check map\n");
	if (!is_closed(s))
	{
		////printf("PAS CLOS\n");
		return (0);
	}
	return (1);
}

t_info prepare_info(void)
{
	t_info i;
	i.posX = 12;
	i.posY = 12;
	i.dirX = -1;
	i.dirY = 0;
	i.planeX = 0.66;
	i.planeY = 0;
	return (i);
}

double degree2radian(double d)
{
	double r;
	r = d * (M_PI / 180);
	return (r);
}

void	pixel_put(int stripe, int y, int color, char *out, t_cub *cub)
{
	printf("stripe=%i, y=%i, cub->rw=%i, cub-rh=%i res=%i\n", stripe, y, cub->rw, cub->rh,54 + (((cub->rw - stripe) * cub->rh) + cub->rh - y) * 4);
	ft_put_int(color, &out, 54 + (((cub->rh - y) * cub->rw) + cub->rw - stripe) * 4);
}


void ft_put_line(int x, int start, int end, t_img *txt, data_t data, int j, int nbt, double wallX, char *out, t_cub *cub)
{
	//////printf("x=%i,	st=%i, end=%i, j=%i, nbt=%i, wallX=%f \n",x,start,end,j,nbt,wallX);
	int i = 0;
	int col;
	int color;
	col = round(wallX * (txt[nbt].nbc - 1)) + 1;
	// if (nbt == 4)
	//	 col = txt[4].nbc - 2;
	//int color;
	while (i < j)
	{
		if (i < start)
			pixel_put(x, i, cub->F, out, cub);
		else if (i > end)
			pixel_put(x, i, cub->C, out, cub);
		else
		{
			// if (nbt == 4)
			// ////printf("i=%i, x=%i,	st=%i, end=%i, j=%i, nbt=%i, wallX=%f nbl=%i, nbc=%i\npick c=%i, l=%i\n",i,x,start,end,j,nbt,wallX,txt[nbt].nbl,txt[nbt].nbc, col, (int)round(((i - start) / (double)(end - start)	* (txt[nbt].nbl - 1))) +1);
			//////printf("coord= col=%i l=%d \n",col, (int)round(((i - start) / (double)(end - start)	* (txt[nbt].nbl - 1))) +1);
			color = pick_color(txt[nbt], (int)round(((i - start) / (double)(end - start) * (txt[nbt].nbl - 1))) + 1, col);
			// if (nbt == 4)
			// ////printf("color=%i\n",color);
			//color = pick_color(txt[nbt], col,round((i * 100 / (end - start) / 100 * (txt[nbt].nbl - 1))) +1	);
			//d = i * 256 - j * 128 + (end - start) * 128;
			//texY = ((d * txt[nbt].nbl) / (end - start)) / 256;
			//color = pick_color(txt[nbt], texY + 1, d + 1);
			// if (color == -1)
			//	 ////printf("BLO\n");
			pixel_put(x, i, color, out, cub);
		}
		i++;
	}
}

void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt, char *out);

void rot_vec(double a, t_info *game)
{
	double old;
	old = game->dirX;
	game->dirX = cos(degree2radian(a)) * game->dirX - sin(degree2radian(a)) * game->dirY;
	game->dirY = sin(degree2radian(a)) * old + cos(degree2radian(a)) * game->dirY;
	old = game->planeX;
	game->planeX = cos(degree2radian(a)) * game->planeX - sin(degree2radian(a)) * game->planeY;
	game->planeY = sin(degree2radian(a)) * old + cos(degree2radian(a)) * game->planeY;
}

double ft_calc_vec(double x, double y, double rX, double rY)
{
	double l1;
	double l2;
	double p;
	double co;

	l1 = sqrt(pow(x, 2) + pow(y, 2));
	l2 = sqrt(pow(rX, 2) + pow(rY, 2));
	p = x * rX + y * rY;
	co = (double)p / (l1 * l2);
	co = acos(co);
	co = co * (180 / M_PI);
	return (co);
}

double dist(double posX, double posY, int sx, int sy)
{
	return (((posX - sx) * (posX - sx) + (posY - sy) * (posY - sy)));
}

void	sort_sprite(t_cub *cub, double posX, double posY)
{
	int i = 0;
	int b = 1;
	while(b == 1)
	{
		b = 0;
		while(cub->sx[i + 1] >= 0)
		{
			double n1 = dist(posX, posY, cub->sx[i], cub->sy[i]);
			double n2 = dist(posX, posY, cub->sx[i + 1], cub->sy[i + 1]);
			if (n2 > n1)
			{
				b = 1;
				int t1 = cub->sx[i];
				int t2 = cub->sy[i];
				cub->sx[i] = cub->sx[i + 1];
				cub->sy[i] = cub->sy[i + 1];
				cub->sx[i + 1] = t1;
				cub->sy[i + 1] = t2;
			}
			i++;
		}
	}	
}


void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt, char *out)
{
	if (key == 53)
	{
		mlx_destroy_window(data.mlx_ptr, data.mlx_win);
		return;
	}
	//////printf("MOVE\n");
	int w = cub->rw;
	int h = cub->rh;
	double posX = game->posX;
	double posY = game->posY;
	double dirX = game->dirX;
	double dirY = game->dirY;
	double planeX = game->planeX;
	double planeY = game->planeY;

	double ZBuffer[cub->rw];

	//while (1)
	//{
	//////printf(" FCT dirx = %f diry= %f et posx=%f et posY=%f\n", dirX, dirY, posX, posY);
	//posX = 13;
	for (int x = 0; x < w; x++) // w=width
	{
		double cameraX = 2 * x / (double)w - 1; // cast w en double a verif
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX; // cast (int)double a verif
		int mapY = (int)posY; // represente coord rayon sur map(donc int)
		//////printf("mX =%i, mY=%i\n",mapX,mapY);
		double sideDistX;
		double sideDistY;
		//////printf("rdX=%f, rdY=%f, cmX=%f\n", rayDirX,rayDirY, cameraX);
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY); // Voir double/int
		//////printf("%f %f delta\n",deltaDistX, deltaDistY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		// int sprite = 0;
		// int spriteX = 0;
		// int allow = 0;
		//////printf("EDGE\n");
		int i = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//////printf("char map %i %i = %c\n", mapX,mapY,cub->map[mapX][mapY]);
			if (cub->map[mapX][mapY] - 48 == 1)
			{
				//////printf("HIT x=%f y=%f et x=%i et w=%i et raydirX=%f et raydirY=%f\n", dirX, dirY,x,w, rayDirX,rayDirY);
				hit = 1;
			}
			// if (cub->map[mapX][mapY] - 48 == 2 && sprite == 0)
			// {
			//	 sprite = 1;
			// }
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(h / perpWallDist);

			int drawStart = -lineHeight / 2 + h / 2;
			int drawEnd = lineHeight / 2 + h / 2;
			int color;
			double wallX; //where exactly the wall was hit
			if (side == 0)
				wallX = posY + perpWallDist * rayDirY;
			else
				wallX = posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));
			//x coordinate on the texture
			int texX = (int)(wallX * (double)txt[4].nbc);
			if (side == 0 && rayDirX > 0)
				texX = txt[0].nbc - texX - 1; // changer txt nb
			if (side == 1 && rayDirY < 0)
				texX = txt[0].nbc - texX - 1;
			int nbt;
			if (rayDirX > 0) // north ?
			{
				nbt = 0;
			}
			else
			{
				nbt = 1;
			}
			if (side == 1 && rayDirY > 0) // west ?
			{
				nbt = 2;
			}
			else if (side == 1) //east ?
			{
				nbt = 3;
			}
			if (hit == 1)
			{
				ft_put_line(x, drawStart, drawEnd, txt, data, h, nbt, wallX,out, cub);
				//////printf("draw WALL %i\n",i);
				//allow = 1;
			}
			// if (sprite == 1 && allow == 1)
			// {
			//	 //////printf("linesprite %i\n",i);
			//	 ft_sprite_line(txt[4], data, wallX, h, x,drawStart, drawEnd);
			//	 sprite = -1;
			//	 allow = 0;
			// }
			ZBuffer[x] = perpWallDist;
		}
		//FORMER
	}
	// CAST SPRITE

	//sort sprite

	sort_sprite(cub, posX, posY);

	for (int i = 0; cub->sx[i] >= 0; i++)
	{
		//t
		double sp = ((posX - cub->sx[i]) * (posX - cub->sx[i]) + (posY - cub->sy[i]) * (posY - cub->sy[i]));
		////printf("DIST DE %i = %f\n", i, sp);
		//t
		double spriteX = cub->sx[i] + 0.5 - posX;
		double spriteY = cub->sy[i] + 0.5 - posY;
		// ////printf("spX=%f, spY=%f\n",spriteX, spriteY);
		double invDet = 1.0 / (planeX * dirY - dirX * planeY);
		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-1 * planeY * spriteX + planeX * spriteY);

		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

		int spriteHeight = abs((int)(h / transformY));
		int drawStartY = -1 * spriteHeight / 2 + h / 2 - 5;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h)
			drawEndY = h;

		int spriteWidth = abs((int)(h / transformY));
		int drawStartX = -1 * spriteWidth / 2 + spriteScreenX ;
		if (drawStartX < 0)
			drawStartX = 0;
		////printf("DSX= %i\n", drawStartX);
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = w;
		//////printf ("sX=%i, eX=%i, sY=%i, eY=%i\n", drawStartX, drawEndX, drawStartY, drawEndY);
		for (int stripe = drawStartX; stripe < drawEndX + 1; stripe++)
		{
			int texX = (int)((256 * (stripe - (-1 * spriteWidth / 2 + spriteScreenX)) * (txt[4].nbc) / spriteWidth) / 256);

			if (transformY > 0 && stripe >= 0 && stripe < w && transformY < ZBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - h * 128 + spriteHeight * 128;
					int texY = ((d * (txt[4].nbl - 1)) / spriteHeight / 256)	+ 1;// voir index
					printf("tX=%i, tY=%i nbc=%i, nbl=%i\n", texX, texY,txt[4].nbc,txt[4].nbl);
					int color = pick_color(txt[4], texY, texX + 1);
					if (color >= 0)
						pixel_put(stripe, y, color, out, cub);
				}
			}
		}
	}
	////printf("CALL LOOP\n");
	//mlx_loop(data.mlx_ptr);
	//}
}

char **remove_space(char **s, int *x, int *y)
{
	char **out;
	int i;
	int j;
	int m;
	int n;

	i = 0;
	m = 0;
	n = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			j++;
		}
		m = (m > j) ? m : j;
		i++;
	}
	out = malloc(sizeof(char *) * (i + 1));
	out[i] = 0;
	while (i > 0)
	{
		out[i - 1] = malloc(sizeof(char) * (m + 1));
		ft_bzero(out[i - 1], m);
		i--;
	}
	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		n = 0;
		while (s[i][j])
		{
			if (s[i][j] != ' ')
			{
				out[i][n] = s[i][j];
				j++;
				n++;
			}
			else
				j++;
		}
		i++;
	}
	////printf("calc mapx=%i, mapy=%i\n", i, j);
	*x = i;
	*y = (j + 1) / 2;
	return (out);
}

char **ft_prepare_map(char *m, int *x, int *y)
{
	////printf("PREP MAP %s\n", m);
	int i;
	int j;
	char **out;

	i = 0;
	j = 0;
	out = ft_split(m, '\n');
	/*while(out[i])
		{
		////printf("RES=%s\n",out[i]);
		j = 0;
		while(out[i][j])
		{
		out[i][j] -= 48;
		j++;
		}
		i++;
		}*/
	out = remove_space(out, x, y);
	//printf("PREP OUT=%s\n", *out);
	return (out);
}

void locate_player(t_info *game, t_cub *cub)
{
	int i;
	int j;
	//printf("LOCATE\n");
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			////printf("CHECK %i\n",cub->map[i][j]);
			if (cub->map[i][j] == 'N')
			{
				//printf("player : x=%i, j=%i et orientation=N\n", i, j);
				// = N
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->dirX = -1;
				game->dirY = 0;
				game->planeX = 0;
				game->planeY = 0.66;
				return;
			}
			else if (cub->map[i][j] == 'E')
			{
				//printf("player : x=%i, j=%i et orientation=E\n", i, j);
				//E
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->dirX = 0;
				game->dirY = 1;
				game->planeY = 0;
				game->planeX = 0.66;
				return;
			}
			else if (cub->map[i][j] == 'W')
			{
				//printf("player : x=%i, j=%i et orientation=W\n", i, j);
				//W
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->dirX = 0;
				game->dirY = -1;
				game->planeY = 0;
				game->planeX = 0.66;
				return;
			}
			else if (cub->map[i][j] == 'S')
			{
				//printf("player : x=%i, j=%i et orientation=S\n", i, j);
				//S
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->dirX = 1;
				game->dirY = 0;
				game->planeX = 0;
				game->planeY = 0.66;
				return;
			}
			j++;
		}
		i++;
	}
}

t_img *ft_prepare_txt(t_cub cub, data_t data)
{
	t_img *out;
	out = malloc(sizeof(t_img) * 5); // N S E O SP ordre
	int i = 0;
	out[0].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.NO, &(out[0].nbc), &(out[0].nbl));
	out[0].img = mlx_get_data_addr(out[0].img, &(out[0].bpp), &(out[0].lsize), &(out[0].endian));
	//printf("1 SUCCES\n");
	out[1].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.SO, &(out[1].nbc), &(out[1].nbl));
	out[1].img = mlx_get_data_addr(out[1].img, &(out[1].bpp), &(out[1].lsize), &(out[1].endian));
	//printf("2 SUCCES\n");
	out[2].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.EA, &(out[2].nbc), &(out[2].nbl));
	out[2].img = mlx_get_data_addr(out[2].img, &(out[2].bpp), &(out[2].lsize), &(out[2].endian));
	//printf("3 SUCCES\n");
	out[3].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.WE, &(out[3].nbc), &(out[3].nbl));
	out[3].img = mlx_get_data_addr(out[3].img, &(out[3].bpp), &(out[3].lsize), &(out[3].endian));
	//printf("4 SUCCES\n");
	out[4].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.S, &(out[4].nbc), &(out[4].nbl));
	out[4].img = mlx_get_data_addr(out[4].img, &(out[4].bpp), &(out[4].lsize), &(out[4].endian));
	//printf("5 SUCCES\n");
	return (out);
}

void print_map(char **map)
{
	int i = 0;
	//printf("---DEB MAP---\n");
	while (map[i] != NULL)
	{
		//printf("%s\n", map[i]);
		i++;
	}
	//printf("---FIN MAP---\n");
}

int count_sprite(char **s)
{
	int i = 0;
	int j = 0;
	int n = 0;
	while (s[i] != NULL)
	{
		while (s[i][j])
		{
			if (s[i][j] == '2')
				n++;
			j++;
		}
		i++;
		j = 0;
	}
	return (n);
}

void locate_sprite(t_cub *cub)
{
	int nb = count_sprite(cub->map);
	//printf("NBS = %i\n", nb);
	int *x = malloc(sizeof(int) * (nb + 1));
	int *y = malloc(sizeof(int) * (nb + 1));
	x[nb] = -1;
	y[nb] = -1;
	int i = 0;
	int j = 0;
	int k = 0;
	while (cub->map[i] != NULL)
	{
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '2')
			{
				x[k] = i;
				y[k] = j;
				k++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	cub->sx = x;
	cub->sy = y;
}

void ft_put_int(int n, char **s, int of)
{
	int tmp = n;
	tmp = tmp>>24;
	//printf("char tmp = %c\n", (char)tmp);
	s[0][3+of] = (char)tmp;
	tmp = n;
	tmp = tmp>>16;
	tmp = tmp & 0b00000000000000000000000011111111;
	//printf("char tmp = %c\n", (char)tmp);
	s[0][2+of] = (char)tmp;
	tmp = n;
	tmp = tmp>>8;
	tmp = tmp & 0b00000000000000000000000011111111;
	//printf("char tmp = %c\n", (char)tmp);
	s[0][1+of] = (char)tmp;
	tmp = n;
	tmp = tmp & 0b00000000000000000000000011111111;
	//printf("char tmp = %c\n", (char)tmp);
	s[0][0+of] = tmp;
}

char *prepare_out(int w, int h)
{
	char *out;
	int tailletot = (w * h * 4) + 54 / 4;
	out = malloc(sizeof(char) * ((w * h * 4) + 54));
	out[0] = 'B';
	out[1] = 'M';
	ft_put_int(tailletot, &out, 2);
	//printf("out=%s\n\n",out);
	int offset = 54;
	ft_put_int(offset, &out, 10);
	int tailletete = 40;
	ft_put_int(tailletete, &out,14);
	ft_put_int(w, &out, 18);
	ft_put_int(h, &out, 22);
	out[26] = (char)1;
	out[27] = (char)0; // nbplan
	int bpp = 32;
	ft_put_int(bpp, &out, 28);
	int compression = 0;
	ft_put_int(compression, &out, 30); // overlap bpp !!!
	int tailleimg = w * h;
	ft_put_int(tailleimg, &out, 34);
	int resH = 1000;
	int resV = 1000;
	ft_put_int(resH, &out, 38);
	ft_put_int(resV, &out, 42);
	ft_put_int(0, &out, 46);
	ft_put_int(0, &out, 50);
	//out[55] = '\0';
	//write(1, out, 56);
	return (out);
}

int main(int ac, char **argv)
{
	if (ac == 3)
	{
		//printf("save img\n");
	}
	else if (ac == 1)
	{
		//printf("Error\n Pas de fichier en argument\n");
		return (0);
	}
	if (check_ext(argv[1]) == 0)
	{
		//printf("Error\n Extension fausse\n");
		return (0);
	}
	int fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
	{
		//printf("Error\nEchec de read\n");
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
	//printf("fd=%i\n", fd);
	while ((k = get_next_line(fd, &line)) != 0)
	{
		if (stat == 1 && ft_strtrim(line, " ")[0] != '1')
		{
			//printf("Error\nMap coupé ou manque de mur\n");
			return (0);
		}
		if (stat == 0)
		{
			////printf("TOFILL line=%s\n", line);
			fill_cub(ft_split(line, ' '), &cub);
		}
		////printf("line=%s\n", line);
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
	////printf("line=%s\n", line);
	if (try_path(&cub) == -1)
	{
		//printf("Error\nChemins non valides");
		return (0);
	}
	if (cub.F == -1 || cub.C == -1)
	{
		//printf("Error\nMauvaises couleurs\n");
		return (0);
	}
	//printf("---MAP---\n%s---FIN MAP---\n", map);
	int border = check_border(map);
	if (!border)
	{
		//printf("Error\nManque de mur\n");
		return (0);
	}

	char **g_map;
	g_map = ft_prepare_map(map, &cub.mx, &cub.my);
	////printf("M01 %i %i\n", g_map[0][0], g_map[0][1]);
	print_cub(cub);
	cub.map = g_map;
	t_info game = prepare_info();
	locate_player(&game, &cub);
	print_map(g_map);
	locate_sprite(&cub);
	////printf("x1=%i,y1=%i,x2=%i,y2=%i\n",cub.sx[0],cub.sy[0],cub.sx[1],cub.sy[1]);
	//fin parsing debut jeu
	// SaVE
	
	// FIN SAVE
	
	data_t data;
	int w = cub.rw;
	int h = cub.rh;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	// if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w, h, "Hello world")) == NULL)
	// 	return (EXIT_FAILURE);
	t_img *txt = ft_prepare_txt(cub, data);
	//game.w = w;
	//game.h = h;
	t_wrap wrap;
	wrap.data = &data;
	wrap.game = &game;
	wrap.cub = &cub;
	wrap.img = txt;
	//mlx_key_hook(data.mlx_win, done, &wrap);
	//mlx_hook()
	char *out;
	out = prepare_out(w,h);
	printf("width = %i\n", w);
	fct_test(data, -1, &game, &cub, txt, out);
	int oo = open("save.bmp", O_WRONLY);
	write(oo, out, 60054);
	write(1, "\n", 1);
	close(oo);
	close(fd);
	free(txt);
	free(g_map);
	//system("leaks a.out");
	return (0);
}