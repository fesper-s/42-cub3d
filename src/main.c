/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/28 14:05:17 by fesper-s         ###   ########.fr       */
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
	raycasting(game);
	handle_keys(game);
	//mlx_clear_window(game->mlx, game->mlx_win);
	return (0);
}

int	cub3d(char *path, t_map *map, t_game *game)
{
	//checagem e tratamento de erro do mapa
	check_map(path, map);
	get_texture(map);

	//inicialização de váriaveis
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
	game->pl->old_pldir_x = 0;
	game->ray->old_plane_x = 0;

	//inicialização da variável posição e direção do player
	pl_pos(game, map);

	//jogo começa
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 640, 480, "Wolfenstein 3D");
	raycasting(game);
	//permite utilizar o teclado para se movimentar no jogo
	mlx_hook(game->mlx_win, 2, (1L << 0), key_press, game);

	mlx_hook(game->mlx_win, 3, (1L << 1), key_release, game);

	//permite fechar a janela ao apertar no X, enviando para uma função de exiting game
	mlx_hook(game->mlx_win, 17, 0, close_game, game);

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
