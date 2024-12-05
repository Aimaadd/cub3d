/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/05 16:05:46 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	args_suffix_checker(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		return (write(1, "Error\n", 6), exit(1), 1);
	return (0);
}

int init_mlx(t_base *base)
{
    base->mlx = malloc(sizeof(t_mlx));
    if (!base->mlx)
        return (error_handler("Error"), 1);
    base->mlx->ptr = mlx_init();
    if (!base->mlx->ptr)
        return (error_handler("Error"), 1);
    base->mlx->width = WIDTH;
    base->mlx->height = HEIGHT;
    base->mlx->win = mlx_new_window(base->mlx->ptr, base->mlx->width, base->mlx->height, "cub3D");
    if (!base->mlx->win)
        return (error_handler("Error"), 1);
    base->data->img = mlx_new_image(base->mlx->ptr, WIDTH, HEIGHT);
    if (!base->data->img)
        return (error_handler("Error"), 1);
    base->data->addr = mlx_get_data_addr(base->data->img, &base->data->bits_per_pixel, &base->data->line_length, &base->data->endian);
    if (!base->data->addr)
        return (error_handler("Error"), 1);
    printf("Image info: bpp=%d, line_length=%d, endian=%d\n",
           base->data->bits_per_pixel,
           base->data->line_length,
           base->data->endian);
    return (0);
}

void    print_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    t_base *base;
    char *test_map[] = {
    "111111111",
    "100000001",
    "100000001",
    "100N00001",
    "111011111",
    "100000001",
    "100000001",
    "111111111",
    NULL
};
    pid_t pid;
    
    // Lancer le script de musique en arrière-plan
    pid = fork();
    if (pid == 0) {
        // Processus enfant
        char *music_args[] = {"afplay", "./music/music.mp3", NULL};
        execvp("afplay", music_args);
        perror("Erreur lors du lancement de la musique");
        exit(1);
    } else if (pid < 0) {
        perror("Erreur lors du fork");
    }
    
    (void)argc;
    (void)argv;
    base = malloc(sizeof(t_base));
    if (!base)
        return (error_handler("Error"), 1);
    initialization(base, argv);
    if (!base->data || !base->mlx)
        return(error_handler("Error"), free(base), 1);
    
    // Utiliser la map de test
    base->data->map = test_map;
    if (valid_map(base) == 1)
        return (printf("Map invalide\n"), 1);
    
    // Afficher la map et les informations du joueur
    print_map(base->data->map);
    printf("Position joueur: x=%f, y=%f, dir=%c\n", 
           base->player->pos_x, 
           base->player->pos_y, 
           base->player->dir);
    game_loop(base);
    
    // Libération de la mémoire
    free(base->mlx);
    free(base->data);
    free(base->player);
    free(base->map);
    free(base->text);
    free(base);
    
    // Arrêter la musique
    if (pid > 0)
        kill(pid, SIGTERM);
    return (0);
}
