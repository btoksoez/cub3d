#include "includes/minilibx-linux/mlx.h"
#include <stdio.h>

int main()
{
    void *mlx;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("mlx_init() failed\n");
        return 1;
    }
    printf("mlx_init() succeeded\n");
    return 0;
}
