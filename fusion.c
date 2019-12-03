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

#define RED get_color(255,0,0)
#define ORANGE get_color(255,128,0)
#define BLUE get_color(0,0,255)
#define GREY get_color(112, 112, 112)
#define PINK get_color(255,176,176)
#define PURPLE get_color(255, 0, 255)
#define YELLOW get_color(255, 251, 0)

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

}               t_cub;

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
    t_cub *cub;
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

void print_cub(t_cub c)
{
    printf("---CUB---\nrw=%i, rh=%i, F=%i, C=%i, NO=%s, SO=%s, WE=%s, EA=%s\n---FIN---\n",c.rw,c.rh,c.F,c.C,c.NO,c.SO,c.WE, c.EA);
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
    while(s[0] != 0)
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
    while(tmp[i])
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

    if(s[0] != 0)
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
    while(s[i])
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
    while(s[i])
    {
        if (!is_in_map(s[i]))
            return (0);
        i++;
    }
    printf("2nd part check map\n");
    if (!is_closed(s)) {
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
void fct_test(data_t data, int key, t_info *game, t_cub *cub);

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
    t_cub *cub = wrap->cub;
    //printf("DONE1 key=%i dirx = %f diry= %f et posx=%f et posY=%f\n",key, game->dirX, game->dirY, game->posX, game->posY);
    printf("key=%i\n",key);
    if (key == 13 || key == 122) // avance 13 mac 122 ubuntu
    {
        game->posX += game->dirX * 0.8;
        game->posY += game->dirY * 0.8;
    }
    else if (key == 1 || key == 115) // recule 1 mac 115 ubuntu
    {
        game->posX -= game->dirX * 0.8;
        game->posY -= game->dirY * 0.8;
    }
    else if (key == 12 || key == 113) //rot gauche 12 mac 113 ubuntu
    {
        rot_vec(-20, game);
    }
    else if (key == 14 || key == 100) //rot droite 14 mac 100 ubuntu
    {
        rot_vec(20, game);
    }
    else
    {
    }
    //printf("DONE2 key=%i dirx = %f diry= %f et posx=%f et posY=%f\n",key, game->dirX, game->dirY, game->posX, game->posY);
    //printf("posx=%f done\n",game.posX);
    fct_test(*data, key, game, cub);
    return (1);
}

void fct_test(data_t data, int key, t_info *game, t_cub *cub)
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
            //if (worldMap[mapX][mapY] > 0)
            //printf("char map %i %i = %c\n", mapX,mapY,cub->map[mapX][mapY]);
            if (cub->map[mapX][mapY] - 48 > 0  && cub->map[mapX][mapY] != 'N' && cub->map[mapX][mapY] != 'E' && cub->map[mapX][mapY] != 'S' && cub->map[mapX][mapY] != 'W') {
                //printf("HIT %i %i\n", mapX, mapY);
                hit = 1;
            }
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
            //if (worldMap[mapX][mapY] == 1)
            if (cub->map[mapX][mapY] - 48 == 1)
                color = RED;
            //else if (worldMap[mapX][mapY] == 2)
            else if (cub->map[mapX][mapY] - 48 == 2)
                color = ORANGE;
            //else if (worldMap[mapX][mapY] == 3)
            else if (cub->map[mapX][mapY] - 48 == 3)
                color = PINK;
            //else if (worldMap[mapX][mapY] == 4)
            else if (cub->map[mapX][mapY] - 48 == 4)
                color = PURPLE;
            else
                color = PINK;

            if (side == 1)
                color = color / 2;
            //if (worldMap[mapX][mapY] >= 1 )
            if (cub->map[mapX][mapY] - 48 >= 1 && cub->map[mapX][mapY] != 'N' && cub->map[mapX][mapY] != 'E' && cub->map[mapX][mapY] != 'S' && cub->map[mapX][mapY] != 'W')
            {
                ft_put_line(x, drawStart, drawEnd, color, data, h);
            }
        }
    }
    mlx_loop(data.mlx_ptr);
    //}
}

char **remove_space(char **s)
{
    char **out;
    int i;
    int j;
    int m;
    int n;

    i = 0;
    m = 0;
    n = 0;
    while(s[i])
    {
        j = 0;
        while(s[i][j])
        {
            j++;
        }
        m = (m > j) ? m : j;
        i++;
    }
    out = malloc(sizeof(char*) * (i + 1));
    out[i] = 0;
    while(i > 0)
    {
        out[i - 1] = malloc(sizeof(char) * (m + 1));
        ft_bzero(out[i- 1], m);
        i--;
    }
    i = 0;
    j = 0;
    while(s[i])
    {
        j = 0;
        n = 0;
        while(s[i][j])
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
    return (out);
}

char **ft_prepare_map(char *m)
{
    printf("PREP MAP %s\n",m);
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
    out = remove_space(out);
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
        while(cub->map[i][j])
        {
            //printf("CHECK %i\n",cub->map[i][j]);
            if (cub->map[i][j] == 'N')
            {
                printf("player : x=%i, j=%i et orientation=N\n",i,j);
                // = N
                game->posX = i;
                game->posY = j;
                game->dirX = -1;
                game->dirY = 0;
                return;
            }
            else if (cub->map[i][j] == 'E')
            {
                printf("player : x=%i, j=%i et orientation=E\n",i,j);
                //E
                game->posX = i;
                game->posY = j;
                game->dirX = 0;
                game->dirY = 1;
                return;
            }
            else if (cub->map[i][j] == 'W')
            {
                printf("player : x=%i, j=%i et orientation=W\n",i,j);
                //W
                game->posX = i;
                game->posY = j;
                game->dirX = 0;
                game->dirY = -1;
                return;
            }
            else if (cub->map[i][j] == 'S')
            {
                printf("player : x=%i, j=%i et orientation=S\n",i,j);
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
    printf("fd=%i\n",fd);
    while((k = get_next_line(fd, &line)) != 0)
    {
        if (stat == 1 && ft_strtrim(line, " ")[0] != '1')
        {
            printf("Error\nMap coupé ou manque de mur\n");
            return (0);
        }
        if (stat == 0)
        {
            printf("TOFILL line=%s\n",line);
            fill_cub(ft_split(line, ' '), &cub);
        }
        printf("line=%s\n",line);
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
    printf("---MAP---\n%s---FIN MAP---\n",map);
    int border = check_border(map);
    if (!border)
    {
        printf("Error\nManque de mur\n");
        return (0);
    }

    char **g_map;
    g_map = ft_prepare_map(map);
    printf("%i %i\n",g_map[0][0], g_map[0][1]);
    cub.map = g_map;
    t_info game = prepare_info();
    locate_player(&game, &cub);

    //fin parsing debut jeu
    data_t        data;
    int w = 512;
    int h = 384;
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, w,h, "Hello world")) == NULL)
        return (EXIT_FAILURE);

    game.w = w;
    game.h = h;
    t_wrap wrap;
    wrap.data = &data;
    wrap.game = &game;
    wrap.cub = &cub;
    mlx_key_hook(data.mlx_win, done, &wrap);
    fct_test(data, -1, &game, &cub);
    close(fd);
    return (0);
}