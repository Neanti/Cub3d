#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

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
	while(g < 20)
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

int pick_color(t_img img, int x, int y)
{
	int i;

	int k = (x - 1) * img.nbc * (img.bpp / 8) + (y - 1) * (img.bpp / 8);
	//printf("%s\n",s);
	i = 0;
	//int k = 0;
	int l = 0;
	char *s = img.img;
	printf("k=%i\n",k);
	while(i < img.bpp)
	{
		//printf("\n\nk=%i, i%i\n\n", k,i);
      	printf("%d", !!((s[k] << l) & 0x80));
		i++;
		l++;
		if (i % 8 == 0)
		{
			printf(".");
			k++;
			l = 0;
		}
	}
	printf("END\n");
	return (8);
}

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 100, 100, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	int i = 2;
	int j = 2;
	void* img = mlx_xpm_file_to_image(data.mlx_ptr, "proto.xpm", &i, &j);
	int bpp;
	int size_line;
	int endian;
	//printf("YO\n");
	char *s = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	t_img im;
	im.img = s;
	im.endian = endian;
	im.bpp = bpp;
	im.lsize = size_line;
	im.nbc = i;
	im.nbl = j;
	printf("i=%i, j=%i, bpp=%i, size_line=%i, endian=%i\n%i\n",i,j, bpp, size_line, endian,(int)s);
	disp(s);
	printimg(im);
	pick_color(im, 3, 1);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img, 0, 0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}