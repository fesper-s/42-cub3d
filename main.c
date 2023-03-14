/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/14 12:18:54 by gussoare         ###   ########.fr       */
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
	int i = -1;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	cub3d(argv[1], &map);
	printf("--------Printing Map-------\n");
	while (map.map[++i])
		printf("%s\n", map.map[i]);
	printf("--------Printing Sprites Paths-------\n");
	printf("%s\n", map.north);
	printf("%s\n", map.south);
	printf("%s\n", map.east);
	printf("%s\n", map.west);
	printf("%s\n", map.floor);
	printf("%s\n", map.ceiling);
	return (0);
}
