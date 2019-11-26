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

int arrange(char *s)
{
    return (0);
}

int check_id(char *s)
{
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
        cub->F = arrange(s[1]);
    }
    else if (id == 8)
    {
        cub->C = arrange(s[1]);
    }
    ft_split_free(s);
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
    printf("fd=%i\n",fd);
    while((k = get_next_line(fd, &line)) != 0)
    {
        fill_cub(ft_split(line, ' '), &cub);
        printf("line=%s\n",line);
        free(line);
    }
    printf("line=%s\n", line);
    print_cub(cub);
    return (0);
}