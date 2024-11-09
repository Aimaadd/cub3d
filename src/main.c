/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/09 18:46:32 by abentaye         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_base *base;
	
	read_map_file(argv[1]);
	args_suffix_checker(argc, argv);
	base = NULL;
	base = initialization(base);
	if (base == NULL)
		return (1);
	return (0);
}
