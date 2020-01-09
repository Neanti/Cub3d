#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "Libft/libft.h"

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

typedef struct s_img
{
	void *img;
	int nbl;
	int nbc;
	int bpp;
	int lsize;
	int endian;
}				t_img;

void printimg(t_img img)
{
	printf("--IMG--\nimg=%p, nbl=%i, nbc=%i, bpp=%i, lsize=%i, endian=%i\n--IMG--\n",img.img,img.nbl,img.nbc,img.bpp,img.lsize,img.endian);
}

void disp(char *s)
{
	int j = 0;
	int l;
	int m;
	int k = 0;
	int i;
	int g = 0;
	while(g < 5)
	{
		k = 0;
	while(k < 4)
	{
  	for (i = 0; i < 8; i++) {
      printf("%d", !!((s[k + (g*4)] << i) & 0x80));
  }
  	printf(".");

  k++;
	}
  printf("\n");
  g++;
	}
}

char *add_char(char *s, int n)
{
	char *out;
	int l = ft_strlen(s);

	out = malloc(sizeof(char) * (l + 2));
	out[l+1] = '\0';
	int i = 0;
	while(i < l)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = n + 48;
	free(s);
	return (out);
}

int get_color(int r, int g, int b)
{
    int o = 0;
    o = r;
    o = o << 8;
    o = o + g;
    o = o << 8;
    o = o + b;
    return (o);
}

char *swap(char *s)
{
	int i = 0;
	int l = ft_strlen(s);
	int k = 7;
	char c;
	int n = 0;
	printf("\nORIG=%s\n",s);
	while(k != l - 1)
	{
		
		//printf("i=%i, k=%i, l=%i\n",i,k,l);
		while(i < k)
		{
			//printf("\t\ti=%i, k=%i\n",i,k);
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
	printf("SWAP=%s\n",s);
	return (s);
}

int deal_pack(char *s)
{
	int i = 0;
	int k = 8;
	int b = 128;
	int so = 0;
	while(i < k)
	{
		so = so + b * (s[i] - 48);
		b = b / 2;
		i++;
	}
	printf("PAR=%d\n",so);
	return (so);
}

int bin2col(char *s, int endian)
{
	int i = 0;
	char *out;
	// if (endian == 0)
	// 	out = swap(s);
	// else
	// {
	// 	out = s;
	// }
	out = s;
	int t[3];
	t[0] = deal_pack(out);
	t[1] = deal_pack(out + 8);
	t[2] = deal_pack(out + 16);
	int c;
	if (endian == 0)
		c = get_color(t[2], t[1], t[0]);
	else
	{
		c = get_color(t[0], t[1], t[2]);
	}
	
	return (c);
}

int pick_color(t_img img, int x, int y)
{
	int i;
	char *res;
	res = malloc(sizeof(char) * (img.bpp + 1));//a check
	res[0] = '\0';
	int k = (x - 1) * img.nbc * (img.bpp / 8) + (y - 1) * (img.bpp / 8);
	//printf("%s\n",s);
	i = 0;
	//int k = 0;
	int l = 0;
	char *s = img.img;
	//printf("k=%i\n",k);
	while(i < img.bpp)
	{
		//printf("\n\nk=%i, i%i\n", k,i);
      	//printf("%d", !!((s[k] << l) & 0x80));
		res = add_char(res, !!((s[k] << l) & 0x80));
		i++;
		l++;
		if (i % 8 == 0)
		{
			printf(".");
			k++;
			l = 0;
		}
	}
	//printf("RES=%s\n",res);
	int color = bin2col(res, img.endian);
	if (res[img.bpp - 1] == '1')
		color = -1;
	printf("END et RES=%s\n",res);
	return (color);
}
int done(int key, void *a)
{
	data_t *d = a;
	mlx_destroy_window(d->mlx_ptr, d->mlx_win);
	printf("done\n");
	exit(1);
	return (1);
}

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 500, 300, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	int j;
	void *img = mlx_new_image(data.mlx_ptr, 500, 300);
	int i = 0;
	int bpp;
	int sl;
	int endian;
	char *ar = mlx_get_data_addr(img, &bpp, &sl, &endian);

	while(i < 50000)
	{
		ar[i] = (char)128;
		i++;
		ar[i] = (char)0;
		i++;
		ar[i] = (char)128;
		i++;
		ar[i] = (char)63;
		i++;
	}
	printf("bp=%i\n",bpp);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img,0,0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}