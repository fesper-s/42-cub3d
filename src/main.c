/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/10 09:46:51 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_game *game)
{	
	float	speed;

	speed = 0.08;
	ft_bzero(game->img->addr, game->height * game->width * \
		(game->img->bpp / 8));
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	vertical_movement(game, speed);
	horizontal_movement(game, speed);
	camera_movement(game, speed);
	return (0);
}

int	cub3d(char *path, t_map *map, t_game *game)
{
	check_map(path, map);
	get_texture(map);
	init_var(game, map);
	pl_pos(game, map);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 640, 480, "Wolfenstein 3D");
	game->img->img = mlx_new_image(game->mlx, 640, 480);
	game->img->addr = mlx_get_data_addr(game->img->img, \
		&game->img->bpp, &game->img->line_len, &game->img->endian);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_game		game;
	t_raycast	ray;
	t_player	pl;
	t_image		img;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	game.ray = &ray;
	game.pl = &pl;
	game.img = &img;
	cub3d(argv[1], &map, &game);
	free_game(&game);
	return (0);
}
