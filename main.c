#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "minilibx/mlx.h"
#include <sys/types.h>
#include <math.h>


#define RED get_color(255,0,0)
#define ORANGE get_color(255,128,0)

size_t strlcpy(char *dst, const char *src, size_t dsize)
{
    const char *osrc = src;
    size_t nleft = dsize;

    /* Copy as many bytes as will fit. */
    if (nleft != 0) {
        while (--nleft != 0) {
            if ((*dst++ = *src++) == '\0')
                break;
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src. */
    if (nleft == 0) {
        if (dsize != 0)
            *dst = '\0';		/* NUL-terminate dst */
        while (*src++)
            ;
    }

    return(src - osrc - 1);	/* count does not include NUL */
}

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int put_square(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
    int i = x1;
    int j = y1;

    while(i < x2)
    {
        while(j < y2)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
            j++;
        }
        j = x1;
        i++;
    }
    return (0);
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

int main(void)
{
    data_t        data;
    int x = 1;
    int y = 1;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    int a = 555555555;
    put_square(data.mlx_ptr, data.mlx_win, 8,8,50,50, get_color(255,255,255));
    put_square(data.mlx_ptr, data.mlx_win, 300,300,350,350, RED);
    mlx_string_put(data.mlx_ptr, data.mlx_win, 60, 60, RED, "yo les bitches\n");
    void *img = mlx_xpm_file_to_image(data.mlx_ptr, "test.xpm", &x, &y);
    mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img, 100, 100);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
