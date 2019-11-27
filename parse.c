#include "Libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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

}               t_cub;

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
    if (!s[1])
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

    ft_split_free(s);
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

    close(fd);
    return (0);
}