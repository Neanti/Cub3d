#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

#define RED get_color(255,0,0)
#define ORANGE get_color(255,128,0)
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

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    int a = 555555555;
    put_square(data.mlx_ptr, data.mlx_win, 8,8,50,50, get_color(255,255,255));
    put_square(data.mlx_ptr, data.mlx_win, 300,300,350,350, RED);
    mlx_string_put(data.mlx_ptr, data.mlx_win, 60, 60, RED, "yo les bitches\n");
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
