/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/12 15:48:30 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	args_suffix_checker(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Error: argument\n", 16), exit(1), 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		return (write(1, "Need a .cub file\n", 18), exit(1), 1);
	return (0);
}

int main(int argc, char **argv)
{
    t_base *base;

    base = malloc(sizeof(t_base));
    if (!base)
        return (error_handler("Allocation failed"), 1);
    initialization(base);
    if (!base->data || !base->mlx)
		return(error_handler("Error"), free(base), 1);
    args_suffix_checker(argc, argv);
    base->data->map = read_map_file(argv[1]);
    if (!base->data->map)
        free(base);
    if (!base->data->map)
        return (free(base->data), free(base->mlx), free(base), 1);
	mlx_loop(base->mlx->ptr);
    return (0);
}
