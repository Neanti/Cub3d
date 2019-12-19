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

int main()
{
	int col = round (0.9 * 100 * (4 - 1) / 100) + 1;
	printf("col=%d\n",col);
	int t = round((298 * 100 / (double)(299 - 0) / 100 * (4 - 1))) + 1;
	int t2 = round((299 * 100 / (299 - 0) / 100 * (4 - 1))) + 1;
	//round((i * 100 / (end - start) / 100 * (txt[nbt].nbl - 1))) +1 
	printf("LI=%d LI2=%i\n",t,t2);

}