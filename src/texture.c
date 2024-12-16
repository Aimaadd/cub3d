#include "../includes/cub3d.h"

static int load_single_texture(t_base *base, t_texture_data *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(base->mlx->ptr, path, 
                                    &tex->width, &tex->height);
    if (!tex->img)
        return (1);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
                                 &tex->line_length, &tex->endian);
    if (!tex->addr)
        return (1);
    return (0);
}

int load_textures(t_base *base)
{
    if (load_single_texture(base, &base->textures[0], base->text->NO) ||
        load_single_texture(base, &base->textures[1], base->text->SO) ||
        load_single_texture(base, &base->textures[2], base->text->WE) ||
        load_single_texture(base, &base->textures[3], base->text->EA))
    {
        return (1);
    }
    return (0);
}

static unsigned int get_pixel_color(t_texture_data *tex, int x, int y)
{
    char    *pixel;
    int     offset;

    if (!tex || !tex->addr || x < 0 || y < 0 || 
        x >= tex->width || y >= tex->height)
        return (0xFF000000);  // Couleur noire en cas d'erreur

    offset = (y * tex->line_length + x * (tex->bits_per_pixel / 8));
    if (offset < 0)
        return (0xFF000000);
        
    pixel = tex->addr + offset;
    return (*(unsigned int *)pixel);
}

void draw_textured_line(t_data *data, int x, int start, int end, 
                       t_texture_data *tex, int tex_x)
{
    double step;
    double tex_pos;
    int tex_y;
    
    if (!tex || !tex->addr || tex_x < 0 || tex_x >= tex->width)
        return;
        
    if (end <= start)
        return;
        
    step = 64.0 / (end - start);
    tex_pos = 0;
    
    for (int y = start; y < end && y < HEIGHT; y++) {
        if (y >= 0) {
            tex_y = (int)tex_pos & 63;
            unsigned int color = get_pixel_color(tex, tex_x, tex_y);
            my_mlx_pixel_put(data, x, y, color);
        }
        tex_pos += step;
    }
}

int verify_texture_dimensions(t_base *base) {
    for (int i = 0; i < 4; i++) {
        if (base->textures[i].width != 64 || base->textures[i].height != 64) {
            printf("Erreur: La texture %d n'a pas les dimensions 64x64\n", i);
            return (1);
        }
    }
    return (0);
}