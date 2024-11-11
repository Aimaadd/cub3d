#include "../../includes/cub3d.h"


static int init_base_data(t_base *base)
{
    base->data = malloc(sizeof(t_data));
    if (!base->data)
        return (1);
    base->data->addr = NULL;
    base->data->bits_per_pixel = 0;
    base->data->endian = 0;
    base->data->img = NULL;
    base->data->line_length = 0;
    base->data->map = NULL;
    return (0);
}

static int mlx_setup(t_mlx **mlx)
{
    *mlx = malloc(sizeof(t_mlx));
    if (!*mlx)
        return (1);
    (*mlx)->ptr = mlx_init();
    if (!(*mlx)->ptr)
        return (1);
    (*mlx)->win = mlx_new_window((*mlx)->ptr, WIDTH, HEIGHT, "cub3D");
    if (!(*mlx)->win)
        return (1);
    return (0);
}

void initialization(t_base *base)
{
    if (init_base_data(base) == 1)
        error_handler("Allocation failed");
    if (!base->data)
    {
        free(base);
        error_handler("Allocation error");
    }
    if (mlx_setup(&base->mlx) == 1)
    {
        free(base->data);
        free(base);
        error_handler("MLX setup failed");
    }
}
