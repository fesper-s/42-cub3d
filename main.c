/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/22 14:22:43 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int key, t_game *game)
{
	t_player	*pl;

	pl = game->pl;
	printf("position_x--> %f\n", game->pl->pl_x);
	printf("position_y--> %f\n", game->pl->pl_y);
	printf("direction_x--> %f\n", game->pl->pldir_x);
	printf("direction_y--> %f\n", game->pl->pldir_y);
	if (key == UP_KEY)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		printf("HELLO\n");
		pl->pl_x += 0.5;
		// if (game->map->map[(int)(pl->pl_x + pl->pldir_x * 0.5)][(int)pl->pl_y] == '0')
		// {
		// 	printf("if 1\n");
		// 	pl->pl_x += pl->pldir_x * 0.5;
		// }
      	// if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y * 0.5)] == '0')
		// {
		// 	printf("if 2\n");
	  	// 	pl->pl_y += pl->pldir_y * 0.5;
		// }
		raycasting(game);
    }
	if (key == DOWN_KEY)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		printf("HELLO\n");
		pl->pl_x -= 0.5;
		// if (game->map->map[(int)(pl->pl_x + pl->pldir_x * 0.5)][(int)pl->pl_y] == '0')
		// {
		// 	printf("if 1\n");
		// 	pl->pl_x += pl->pldir_x * 0.5;
		// }
      	// if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y * 0.5)] == '0')
		// {
		// 	printf("if 2\n");
	  	// 	pl->pl_y += pl->pldir_y * 0.5;
		// }
		raycasting(game);
    }
	if (key == RIGHT_KEY)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		printf("HELLO\n");
		pl->pl_y += 0.5;
		// if (game->map->map[(int)(pl->pl_x + pl->pldir_x * 0.5)][(int)pl->pl_y] == '0')
		// {
		// 	printf("if 1\n");
		// 	pl->pl_x += pl->pldir_x * 0.5;
		// }
      	// if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y * 0.5)] == '0')
		// {
		// 	printf("if 2\n");
	  	// 	pl->pl_y += pl->pldir_y * 0.5;
		// }
		raycasting(game);
    }
	if (key == LEFT_KEY)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		printf("HELLO\n");
		pl->pl_y -= 0.5;
		// if (game->map->map[(int)(pl->pl_x + pl->pldir_x * 0.5)][(int)pl->pl_y] == '0')
		// {
		// 	printf("if 1\n");
		// 	pl->pl_x += pl->pldir_x * 0.5;
		// }
      	// if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y * 0.5)] == '0')
		// {
		// 	printf("if 2\n");
	  	// 	pl->pl_y += pl->pldir_y * 0.5;
		// }
		raycasting(game);
    }
	return (0);
}

int	cub3d(char *path, t_map *map, t_game *game)
{
	check_map(path, map);
	game->pl->pl_x = 0;
	game->pl->pl_y = 0;
	game->pl->pldir_x = 0;
	game->pl->pldir_y = 0;
	game->frame = 0;
	game->old_frame = 0;
	game->map = map;
	game->height = 480;
	game->width = 640;
	game->ray->plane_x = 0;
	game->ray->plane_y = 0.66;
	pl_pos(game, map);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 640, 480, "Wolfenstein 3D");
	printf("position_x--> %f\n", game->pl->pl_x);
	printf("position_y--> %f\n", game->pl->pl_y);
	mlx_clear_window(game->mlx, game->mlx_win);
	raycasting(game);
	mlx_key_hook(game->mlx_win, key_event, game);
	mlx_hook(game->mlx_win, 17, 0, NULL, NULL);
	mlx_loop(game->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_game		game;
	t_raycast	ray;
	t_player	pl;

	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	game.ray = &ray;
	game.pl = &pl;
	cub3d(argv[1], &map, &game);
	int i = -1;
	while (game.map->map[++i])
		printf("%s\n", game.map->map[i]);
	printf("player dir_x--> %f\n", game.pl->pldir_x);
	printf("player dir_y--> %f\n", game.pl->pldir_y);
	free_map(&map);
	return (0);
}
