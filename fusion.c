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

#define RED get_color(255, 0, 0)
#define ORANGE get_color(255, 128, 0)
#define BLUE get_color(0, 0, 255)
#define GREY get_color(112, 112, 112)
#define PINK get_color(255, 176, 176)
#define PURPLE get_color(255, 0, 255)
#define YELLOW get_color(255, 251, 0)

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64

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

typedef struct s_cub
{
    int rw;
    int rh;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *S;
    int F;
    int C;
    char **map;
    int mx;
    int my;
} t_cub;

typedef struct s_img
{
    void *img;
    int nbl;
    int nbc;
    int bpp;
    int lsize;
    int endian;
} t_img;

typedef struct data_s
{
    void *mlx_ptr;
    void *mlx_win;
} data_t;

typedef struct s_info
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    //int h;
    //int w;
} t_info;

typedef struct s_wrap
{
    data_t *data;
    t_info *game;
    t_cub *cub;
    t_img *img;
} t_wrap;

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

void print_cub(t_cub c)
{
    printf("---CUB---\nrw=%i, rh=%i, F=%i, C=%i, NO=%s, SO=%s, WE=%s, EA=%s, S=%s\n---FIN---\n", c.rw, c.rh, c.F, c.C, c.NO, c.SO, c.WE, c.EA, c.S);
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
    int i;
    char *tmp;

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
    int i;
    char *s1;
    char *s2;

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
    char **sp;
    int color;
    int i1;
    int i2;
    int i3;
    char *s2;

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
    //printf("checkid de %s\n\n",s);
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
    int i = 0;
    int l = ft_strlen(s);
    int k = 7;
    char c;
    int n = 0;
    //printf("\nORIG=%s\n",s);
    while (k != l - 1)
    {

        //printf("i=%i, k=%i, l=%i\n",i,k,l);
        while (i < k)
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
    //printf("SWAP=%s\n",s);
    return (s);
}

int deal_pack(char *s)
{
    int i = 0;
    int k = 8;
    int b = 128;
    int so = 0;
    while (i < k)
    {
        so = so + b * (s[i] - 48);
        b = b / 2;
        i++;
    }
    //printf("PAR=%d\n",so);
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

char *add_char(char *s, int n)
{
    char *out;
    int l = (int)strlen(s);

    out = s;
    out[l + 1] = '\0';
    int i = 0;
    while (i < l)
    {
        //out[i] = s[i];
        i++;
    }
    out[i] = n + 48;
    //free(s);
    return (out);
}

int pick_color(t_img img, int x, int y)
{
    // printf("PICK x=%i y=%i\n",x,y);
    int i;
    char *res;
    //res = malloc(sizeof(char) * 1);
    res = malloc(sizeof(char) * (img.bpp + 1));
    res[0] = '\0';
    int k = (x - 1) * img.nbc * (img.bpp / 8) + (y - 1) * (img.bpp / 8);
    //printf("%s\n",s);
    i = 0;
    //int k = 0;
    int l = 0;
    char *s = img.img;
    //printf("k=%i\n",k);
    while (i < img.bpp)
    {
        //printf("\n\nk=%i, i%i\n\n", k,i);
        //printf("%d", !!((s[k] << l) & 0x80));
        res = add_char(res, !!((s[k] << l) & 0x80));
        i++;
        l++;
        if (i % 8 == 0)
        {
            //printf(".");
            k++;
            l = 0;
        }
    }
    int color = bin2col(res, img.endian);
    //printf("RES=%s\n",res);
    if (res[img.bpp - 1] == '1')
        color = -1;
    //printf("END et RES=%s\n",res);
    return (color);
}

int try_fd(char *s)
{
    int fd;
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
    char *out;
    int i;

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
    int i;

    i = 0;
    printf("1st part border\n");
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
    printf("2nd part border\n");
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
    int i;
    int player;

    player = 0;
    i = 0;
    while (s[i])
    {
        if (!is_in_map(s[i]))
            return (0);
        i++;
    }
    printf("2nd part check map\n");
    if (!is_closed(s))
    {
        printf("PAS CLOS\n");
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

void ft_put_line(int x, int start, int end, t_img *txt, data_t data, int j, int nbt, double wallX)
{
    //printf("x=%i,  st=%i, end=%i, j=%i, nbt=%i, wallX=%f \n",x,start,end,j,nbt,wallX);
    int i = 0;
    int col;
    int color;
    col = round(wallX * (txt[nbt].nbc - 1)) + 1;
    // if (nbt == 4)
    //     col = txt[4].nbc - 2;
    //int color;
    while (i < j)
    {
        if (i < start)
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, GREY);
        else if (i > end)
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, BLUE);
        else
        {
            // if (nbt == 4)
            // printf("i=%i, x=%i,  st=%i, end=%i, j=%i, nbt=%i, wallX=%f nbl=%i, nbc=%i\npick c=%i, l=%i\n",i,x,start,end,j,nbt,wallX,txt[nbt].nbl,txt[nbt].nbc, col, (int)round(((i - start) / (double)(end - start)  * (txt[nbt].nbl - 1))) +1);
            //printf("coord= col=%i l=%d \n",col, (int)round(((i - start) / (double)(end - start)  * (txt[nbt].nbl - 1))) +1);
            color = pick_color(txt[nbt], (int)round(((i - start) / (double)(end - start) * (txt[nbt].nbl - 1))) + 1, col);
            // if (nbt == 4)
            // printf("color=%i\n",color);
            //color = pick_color(txt[nbt], col,round((i * 100 / (end - start) / 100 * (txt[nbt].nbl - 1))) +1  );
            //d = i * 256 - j * 128 + (end - start) * 128;
            //texY = ((d * txt[nbt].nbl) / (end - start)) / 256;
            //color = pick_color(txt[nbt], texY + 1, d + 1);
            // if (color == -1)
            //     printf("BLO\n");
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, color);
        }
        i++;
    }
}

void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt);

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

int done(int key, void *a)
{
    t_wrap *wrap = a;
    t_info *game = wrap->game;
    data_t *data = wrap->data;
    t_cub *cub = wrap->cub;
    t_img *txt = wrap->img;
    //printf("DONE1 key=%i dirx = %f diry= %f et posx=%f et posY=%f mapx=%i, mapy=%i\n",key, game->dirX, game->dirY, game->posX, game->posY, cub->mx, cub->my);
    printf("key=%i\n", key);
    if (key == 53 || key == 65307) // mac ubuntu
    {
        printf("LEAVEDONE\n");
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
        exit(0);
        return (0);
    }
    if (key == 13 || key == 122) // avance 13 mac 122 ubuntu
    {
        game->posX += game->dirX * 0.8;
        game->posY += game->dirY * 0.8;
        if (game->posX >= cub->mx - 1 || game->posX <= 1 || game->posY >= cub->my - 1 || game->posY <= 1)
        {
            game->posX -= game->dirX * 0.8;
            game->posY -= game->dirY * 0.8;
        }
    }
    else if (key == 1 || key == 115) // recule 1 mac 115 ubuntu
    {
        game->posX -= game->dirX * 0.8;
        game->posY -= game->dirY * 0.8;
        if (game->posX >= cub->mx - 1 || game->posX <= 1 || game->posY >= cub->my - 1 || game->posY <= 1)
        {
            game->posX += game->dirX * 0.8;
            game->posY += game->dirY * 0.8;
        }
    }
    else if (key == 0 || key == 113) //rot gauche 0 mac 113 ubuntu
    {
        rot_vec(-20, game);
    }
    else if (key == 2 || key == 100) //rot droite 14 mac 100 ubuntu
    {
        rot_vec(20, game);
    }
    else
    {
    }
    //printf("DONE2 key=%i dirx = %f diry= %f et posx=%f et posY=%f\n",key, game->dirX, game->dirY, game->posX, game->posY);
    //printf("posx=%f done\n",game.posX);
    fct_test(*data, key, game, cub, txt);
    return (1);
}

void ft_sprite_line(t_img img, data_t data, double wallX, int h, int x, int start, int end)
{
    int i = start;
    int col = round(wallX * (img.nbc - 1)) + 1;
    int color;
    //printf("DRAW SPRITE\n");
    while (i < end)
    {
        color = pick_color(img, (int)round(((i - start) / (double)(end - start) * (img.nbl - 1))) + 1, col);
        // if (color != -1)
        // printf("color of x=%i,y=%i is %i\n", (int)round(((i - start) / (double)(end - start) * (img.nbl - 1))) + 1, col, color);
        if (color != -1)
            mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, i, color);
        i++;
    }
}

void fct_test(data_t data, int key, t_info *game, t_cub *cub, t_img *txt)
{
    if (key == 53)
    {
        mlx_destroy_window(data.mlx_ptr, data.mlx_win);
        return;
    }
    //printf("MOVE\n");
    int w = cub->rw;
    int h = cub->rh;
    double posX = game->posX;
    double posY = game->posY;
    double dirX = game->dirX;
    double dirY = game->dirY;
    double planeX = game->planeX;
    double planeY = game->planeY;

    double ZBuffer[cub->rw];

    while (1)
    {
        //printf(" FCT dirx = %f diry= %f et posx=%f et posY=%f\n", dirX, dirY, posX, posY);
        //posX = 13;
        for (int x = 0; x < w; x++) // w=width
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
            // int sprite = 0;
            // int spriteX = 0;
            // int allow = 0;
            //printf("EDGE\n");
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
                //printf("char map %i %i = %c\n", mapX,mapY,cub->map[mapX][mapY]);
                if (cub->map[mapX][mapY] - 48 == 1)
                {
                    //printf("HIT x=%f y=%f et x=%i et w=%i et raydirX=%f et raydirY=%f\n", dirX, dirY,x,w, rayDirX,rayDirY);
                    hit = 1;
                }
                // if (cub->map[mapX][mapY] - 48 == 2 && sprite == 0)
                // {
                //     sprite = 1;
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
                int texX = (int)(wallX * (double)texWidth);
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
                    ft_put_line(x, drawStart, drawEnd, txt, data, h, nbt, wallX);
                    //printf("draw WALL %i\n",i);
                    //allow = 1;
                }
                // if (sprite == 1 && allow == 1)
                // {
                //     //printf("linesprite %i\n",i);
                //     ft_sprite_line(txt[4], data, wallX, h, x,drawStart, drawEnd);
                //     sprite = -1;
                //     allow = 0;
                // }
                ZBuffer[x] = perpWallDist;
            }
            //SPRITE CASTING
            //sort sprites from far to close
            for (int i = 0; i < numSprites; i++)
            {
                spriteOrder[i] = i;
                spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
            }
            sortSprites(spriteOrder, spriteDistance, numSprites);

            //after sorting the sprites, do the projection and draw them
            for (int i = 0; i < numSprites; i++)
            {
                //translate sprite position to relative to camera
                double spriteX = sprite[spriteOrder[i]].x - posX;
                double spriteY = sprite[spriteOrder[i]].y - posY;

                //transform sprite with the inverse camera matrix
                // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
                // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
                // [ planeY   dirY ]                                          [ -planeY  planeX ]

                double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

                double transformX = invDet * (dirY * spriteX - dirX * spriteY);
                double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

                int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

                //calculate height of the sprite on screen
                int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
                //calculate lowest and highest pixel to fill in current stripe
                int drawStartY = -spriteHeight / 2 + h / 2;
                if (drawStartY < 0)
                    drawStartY = 0;
                int drawEndY = spriteHeight / 2 + h / 2;
                if (drawEndY >= h)
                    drawEndY = h - 1;

                //calculate width of the sprite
                int spriteWidth = abs(int(h / (transformY)));
                int drawStartX = -spriteWidth / 2 + spriteScreenX;
                if (drawStartX < 0)
                    drawStartX = 0;
                int drawEndX = spriteWidth / 2 + spriteScreenX;
                if (drawEndX >= w)
                    drawEndX = w - 1;

                //loop through every vertical stripe of the sprite on screen
                for (int stripe = drawStartX; stripe < drawEndX; stripe++)
                {
                    int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
                    //the conditions in the if are:
                    //1) it's in front of camera plane so you don't see things behind you
                    //2) it's on the screen (left)
                    //3) it's on the screen (right)
                    //4) ZBuffer, with perpendicular distance
                    if (transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
                        for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                        {
                            int d = (y)*256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                            int texY = ((d * texHeight) / spriteHeight) / 256;
                            Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
                            if ((color & 0x00FFFFFF) != 0)
                                buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
                        }
                }
            }
        }
        printf("CALL LOOP\n");
        mlx_loop(data.mlx_ptr);
    }
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
    printf("calc mapx=%i, mapy=%i\n", i, j);
    *x = i;
    *y = (j + 1) / 2;
    return (out);
}

char **ft_prepare_map(char *m, int *x, int *y)
{
    printf("PREP MAP %s\n", m);
    int i;
    int j;
    char **out;

    i = 0;
    j = 0;
    out = ft_split(m, '\n');
    /*while(out[i])
        {
        printf("RES=%s\n",out[i]);
        j = 0;
        while(out[i][j])
        {
        out[i][j] -= 48;
        j++;
        }
        i++;
        }*/
    out = remove_space(out, x, y);
    return (out);
}

void locate_player(t_info *game, t_cub *cub)
{
    int i;
    int j;
    printf("LOCATE\n");
    i = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            //printf("CHECK %i\n",cub->map[i][j]);
            if (cub->map[i][j] == 'N')
            {
                printf("player : x=%i, j=%i et orientation=N\n", i, j);
                // = N
                game->posX = i;
                game->posY = j;
                game->dirX = -1;
                game->dirY = 0;
                return;
            }
            else if (cub->map[i][j] == 'E')
            {
                printf("player : x=%i, j=%i et orientation=E\n", i, j);
                //E
                game->posX = i;
                game->posY = j;
                game->dirX = 0;
                game->dirY = 1;
                return;
            }
            else if (cub->map[i][j] == 'W')
            {
                printf("player : x=%i, j=%i et orientation=W\n", i, j);
                //W
                game->posX = i;
                game->posY = j;
                game->dirX = 0;
                game->dirY = -1;
                return;
            }
            else if (cub->map[i][j] == 'S')
            {
                printf("player : x=%i, j=%i et orientation=S\n", i, j);
                //S
                game->posX = i;
                game->posY = j;
                game->dirX = 1;
                game->dirY = 0;
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
    printf("1 SUCCES\n");
    out[1].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.SO, &(out[1].nbc), &(out[1].nbl));
    out[1].img = mlx_get_data_addr(out[1].img, &(out[1].bpp), &(out[1].lsize), &(out[1].endian));
    printf("2 SUCCES\n");
    out[2].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.EA, &(out[2].nbc), &(out[2].nbl));
    out[2].img = mlx_get_data_addr(out[2].img, &(out[2].bpp), &(out[2].lsize), &(out[2].endian));
    printf("3 SUCCES\n");
    out[3].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.WE, &(out[3].nbc), &(out[3].nbl));
    out[3].img = mlx_get_data_addr(out[3].img, &(out[3].bpp), &(out[3].lsize), &(out[3].endian));
    printf("4 SUCCES\n");
    out[4].img = mlx_xpm_file_to_image(data.mlx_ptr, cub.S, &(out[4].nbc), &(out[4].nbl));
    out[4].img = mlx_get_data_addr(out[4].img, &(out[4].bpp), &(out[4].lsize), &(out[4].endian));
    printf("5 SUCCES\n");
    return (out);
}

int main(int ac, char **argv)
{
    if (ac == 3)
    {
        printf("save img\n");
    }
    else if (ac == 1)
    {
        printf("Error\n Pas de fichier en argument\n");
        return (0);
    }
    if (check_ext(argv[1]) == 0)
    {
        printf("Error\n Extension fausse\n");
        return (0);
    }
    int fd = open(argv[1], O_RDONLY);
    if (read(fd, NULL, 0) < 0)
    {
        printf("Error\nEchec de read\n");
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
    printf("fd=%i\n", fd);
    while ((k = get_next_line(fd, &line)) != 0)
    {
        if (stat == 1 && ft_strtrim(line, " ")[0] != '1')
        {
            printf("Error\nMap coupé ou manque de mur\n");
            return (0);
        }
        if (stat == 0)
        {
            printf("TOFILL line=%s\n", line);
            fill_cub(ft_split(line, ' '), &cub);
        }
        printf("line=%s\n", line);
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
    printf("line=%s\n", line);
    if (try_path(&cub) == -1)
    {
        printf("Error\nChemins non valides");
        return (0);
    }
    if (cub.F == -1 || cub.C == -1)
    {
        printf("Error\nMauvaises couleurs\n");
        return (0);
    }
    print_cub(cub);
    printf("---MAP---\n%s---FIN MAP---\n", map);
    int border = check_border(map);
    if (!border)
    {
        printf("Error\nManque de mur\n");
        return (0);
    }

    char **g_map;
    g_map = ft_prepare_map(map, &cub.mx, &cub.my);
    printf("%i %i\n", g_map[0][0], g_map[0][1]);
    cub.map = g_map;
    t_info game = prepare_info();
    locate_player(&game, &cub);

    //fin parsing debut jeu
    data_t data;
    int w = cub.rw;
    int h = cub.rh;
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w, h, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    t_img *txt = ft_prepare_txt(cub, data);
    //game.w = w;
    //game.h = h;
    t_wrap wrap;
    wrap.data = &data;
    wrap.game = &game;
    wrap.cub = &cub;
    wrap.img = txt;
    mlx_key_hook(data.mlx_win, done, &wrap);
    //mlx_hook()
    fct_test(data, -1, &game, &cub, txt);
    close(fd);
    free(txt);
    free(g_map);
    system("leaks a.out");
    return (0);
}