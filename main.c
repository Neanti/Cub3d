#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "minilibx/mlx.h"
#include <sys/types.h>
#include <math.h>


#define RED get_color(255,0,0)
#define ORANGE get_color(255,128,0)
#define BLUE get_color(0,0,255)
#define GREY get_color(112, 112, 112)
#define PINK get_color(255,176,176)
#define PURPLE get_color(255, 0, 255)
#define YELLOW get_color(255, 251, 0)

// size_t strlcpy(char *dst, const char *src, size_t dsize)
// {
//     const char *osrc = src;
//     size_t nleft = dsize;

//     /* Copy as many bytes as will fit. */
//     if (nleft != 0) {
//         while (--nleft != 0) {
//             if ((*dst++ = *src++) == '\0')
//                 break;
//         }
//     }

//     /* Not enough room in dst, add NUL and traverse rest of src. */
//     if (nleft == 0) {
//         if (dsize != 0)
//             *dst = '\0';		/* NUL-terminate dst */
//         while (*src++)
//             ;
//     }

//     return(src - osrc - 1);	/* count does not include NUL */
// }

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

typedef struct s_info
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    int h;
    int w;
}           t_info;

typedef struct s_wrap
{
    data_t *data;
    t_info *game;
}              t_wrap;

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

t_info prepare_info(void)
{
    t_info i;
    i.posX = 12;
    i.posY = 12;
    i.dirX = -1;
    i.dirY = 0;
    i.planeX = 0;
    i.planeY = 0.66;
    return (i);
}

double degree2radian(double d)
{
    double r;
    r = d * (M_PI / 180);
    return (r);
}

void ft_put_line(int x, int start, int end, int color , data_t data, int j)
{
    int i = 0;
    while (i < j)
    {
        if (i < start)
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, GREY);
        else if (i > end)
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, BLUE);
        else
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, color);

        i++;
    }
}
void fct_test(data_t data, int key, t_info *game);

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

int done(int key, void *a)
{
    t_wrap *wrap = a;
    t_info *game = wrap->game;
    data_t *data = wrap->data;
    //printf("DONE1 key=%i dirx = %f diry= %f et posx=%f et posY=%f\n",key, game->dirX, game->dirY, game->posX, game->posY);
    if (key == 13)
    {
        game->posX += game->dirX * 0.8;
        game->posY += game->dirY * 0.8;
    }
    else if (key == 1)
    {
        game->posX -= game->dirX * 0.8;
        game->posY -= game->dirY * 0.8;
    }
    else if (key == 12)
    {
        rot_vec(20, game);
    }
    else if (key == 14)
    {
        rot_vec(-20, game);
    }
    else
    {
    }
    //printf("DONE2 key=%i dirx = %f diry= %f et posx=%f et posY=%f\n",key, game->dirX, game->dirY, game->posX, game->posY);
    //printf("posx=%f done\n",game.posX);
    fct_test(*data, key, game);
    return (1);
}

void fct_test(data_t data, int key, t_info *game)
{
    //printf("MOVE\n");
    int w = 512;
    int h = 384;
    // double posX = 8, posY = 12;
    // double dirX = -1, dirY = 0;
    // double planeX = 0, planeY = 0.66;
    double posX = game->posX;
    double posY = game->posY;
    double dirX = game->dirX;
    double dirY = game->dirY;
    double planeX = game->planeX;
    double planeY = game->planeY;
    //while(1)
    //{
        //printf(" FCT dirx = %f diry= %f et posx=%f et posY=%f\n", dirX, dirY, posX, posY);
        //posX = 13;
        for(int x = 0; x < w; x++) // w=wight ????
        {
            double cameraX = 2 * x / (double)w - 1; // cast w en double a verif
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = (int)posX; // cast (int)double a verif
            int mapY = (int)posY; // represente coord rayon sur map(donc int)

            double sideDistX;
            double sideDistY;

            double deltaDistX = fabs(1 / rayDirX);
            double deltaDistY = fabs(1 / rayDirY); // Voir double/int
            //printf("%f %f delta\n",deltaDistX, deltaDistY);
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

            while (hit == 0)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX +=stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
                
                if (side == 0)
                    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
                else
                    perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

                int lineHeight = (int)(h / perpWallDist);

                int drawStart = -lineHeight / 2 + h / 2;
                if (drawStart < 0)
                    drawStart = 0;
                int drawEnd = lineHeight / 2 + h / 2;
                if (drawEnd >= h)
                    drawEnd = h - 1;
                int color;
                if (worldMap[mapX][mapY] == 1)
                    color = RED;
                else if (worldMap[mapX][mapY] == 2)
                    color = ORANGE;
                else if (worldMap[mapX][mapY] == 3)
                    color = PINK;
                else if (worldMap[mapX][mapY] == 4)
                    color = PURPLE;
                else
                    color = PINK;

                if (side == 1)
                    color = color / 2;
                if (worldMap[mapX][mapY] >= 1)
                {
                    ft_put_line(x, drawStart, drawEnd, color, data, h);
                }
            }
        }
        mlx_loop(data.mlx_ptr);
    //}
}

int main(void)
{
    data_t        data;
    int w = 512;
    int h = 384;
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w,h, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    t_info game = prepare_info();
    game.w = w;
    game.h = h;
    t_wrap wrap;
    wrap.data = &data;
    wrap.game = &game;
    mlx_key_hook(data.mlx_win, done, &wrap);
    fct_test(data, -1, &game);
    return (EXIT_SUCCESS);
}
