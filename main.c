/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 14:40:18 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cub3d(char *path, t_map *map)
{
	check_map(path, map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	cub3d(argv[1], &map);
	return (0);
}
