/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/20 14:27:46 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cub3d(char *path, t_map *map, t_game *game)
{
	check_map(path, map);
	init_var(map, game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	cub3d(argv[1], &map, &game);
	int i = -1;
	while (map.map[++i])
		printf("%s\n", map.map[i]);
	printf("player pos_x--> %f\n", game.pl_x);
	printf("player pos_y--> %f\n", game.pl_y);
	printf("player dir_x--> %f\n", game.pldir_x);
	printf("player dir_y--> %f\n", game.pldir_y);
	free_map(&map);
	return (0);
}
