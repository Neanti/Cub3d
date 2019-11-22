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

#define mapWidth 4
#define mapHeight 4

int worldMap[mapWidth][mapHeight]=
        {
                {1,1,1,1},
                {1,0,0,1},
                {1,0,2,1},
                {1,1,1,1}
        };

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

typedef struct s_point
{
    int x;
    int y;
}               t_point;

typedef struct s_player
{
    int Px;
    int Py;
    int size;
    int FOV;
    double ori;
}               t_player;

t_player prepare_player(void)
{
    t_player p;
    p.ori = 0;
    p.FOV = 60;
    p.size = 32;
    p.Px = 0;
    p.Py = 0;
    return (p);
}

typedef struct s_plan
{
    int x;
    int y;
    double ang;
    double dist;
    double act;
}               t_plan;

t_plan prepare_plan(void)
{
    t_plan p;
    p.x = 320;
    p.y = 200;
    p.ang = 0;
    p.dist = 0;
    p.act = -30;
    return (p);
}

void print_point(t_point p)
{
    printf("---tpoint---\n x=%i et y=%i\n---fin tpoint---\n");
}

void print_plan(t_plan p)
{
    printf("---tplan---\nx=%i et y=%i et angle=%f et dist=%f\n---fin tplan---\n", p.x, p.y, p.ang, p.dist);
}

double degree2radian(double d)
{
    double r;
    r = d * (M_PI / 180);
    return (r);
}

void print_player(t_player p)
{
    printf("---tplayer---\nPx=%i et Py=%i et size=%i et FOV=%i et ori=%f\n---fin tplayer---\n", p.Px, p.Py, p.size, p.FOV, p.ori);
}

void get_plan_info(t_player player,t_plan *tplan)
{
    double ang;
    double x;

    ang = player.FOV / 2;
    x = (double)tplan->x / (double)2;
    printf("%f / %f=tan(%f) == %f\n", x, tan(degree2radian(ang)), ang, x / (tan(degree2radian(ang))));
    tplan->dist = x / (tan(degree2radian(ang)));
    tplan->ang = (double)player.FOV / (double)tplan->x;
}

t_point calc_dH(t_player player, t_plan plan)
{
    t_point p;
    int comp;

    if (plan.act < 0)

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
    t_plan plan = prepare_plan();
    t_player player = prepare_player();
    print_plan(plan);
    print_player(player);
    get_plan_info(player, &plan);
    print_plan(plan);
    t_point pointH = calc_dH(player);
    print_point(pointH);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
