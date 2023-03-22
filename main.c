/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/22 12:55:11 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cub3d(char *path, t_map *map, t_game *game)
{
	check_map(path, map);
	init_var(map, game);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 640, 480, "Wolfenstein 3D");
	raycasting(game);
	mlx_loop(game->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_game		game;
	t_raycast   ray;
    t_player    pl;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	get_texture();
	game.ray = &ray;
	game.pl = &pl;
	cub3d(argv[1], &map, &game);
	int i = -1;
	while (game.map->map[++i])
		printf("%s\n", game.map->map[i]);
	printf("player pos_x--> %f\n", game.pl->pl_x);
	printf("player pos_y--> %f\n", game.pl->pl_y);
	printf("player dir_x--> %f\n", game.pl->pldir_x);
	printf("player dir_y--> %f\n", game.pl->pldir_y);
	free_map(&map);
	return (0);
}
