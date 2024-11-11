#include "../../includes/cub3d.h"

static int setup(t_mlx *mlx)
{
    if (!mlx)
        return (1);
    mlx->ptr = NULL;
    mlx->win = NULL;
    mlx->width = 0;
    mlx->length = 0;
    return (0);
}

static int mlx_setup(t_mlx *mlx)
{
    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    if (!mlx)
        error_handler("Allocation error");
    if (setup(mlx) == 0)
    {
        mlx->ptr = mlx_init();
        mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "cub3D");
        mlx_loop(mlx);
    }
    else
        return (1);
    return (0);
}

t_base  *initialization(t_base *base)
{
    base = (t_base *)malloc(sizeof(t_base));
    if (!base)
        error_handler("Allocation error");
    base->data = (t_data *)malloc(sizeof(t_data));
    if (!base->data)
    {
        free(base);
        error_handler("Allocation error");
    }
    if (mlx_setup(base->mlx) == 1)
    {
        free(base->data);
        free(base);
        free(base->mlx);
        return NULL;
    }
    return (base);
}
