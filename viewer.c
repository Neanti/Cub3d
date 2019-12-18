#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

void disp(char *s)
{
	int j = 0;
	int l;
	int m;
	int k = 0;
	int i;
	int g = 0;
	while(g < 1000)
	{
		k = 0;
	while(k < 4)
	{
  	for (i = 0; i < 8; i++) {
      printf("%d", !!((s[k + (g*4)] << i) & 0x80));
  }
  k++;
	}
  printf("\n");
  g++;
	}
}

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	int i = 2;
	int j = 2;
	void* img = mlx_xpm_file_to_image(data.mlx_ptr, "draw.xpm", &i, &j);
	int bpp;
	int size_line;
	int endian;
	printf("YO\n");
	char *s = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	s[0] += 99;
	printf("i=%i, j=%i, bpp=%i, size_line=%i, endian=%i\n%i\n",i,j, bpp, size_line, endian,(int)s);
	disp(s);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img, 0, 0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}