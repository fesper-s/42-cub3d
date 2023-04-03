/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:15:23 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/03 11:24:40 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ver_line(int x, t_game *game)
{
	t_raycast	*ray;
	int			color;
	int i = -1;

	ray = game->ray;

	if (game->map->map[ray->map_x][ray->map_y] == '1')
		color = 0x40E0D0;
	if (game->map->map[ray->map_x][ray->map_y] == '2')
		color = 0xFF5555;
	if (ray->side == 1)
		color = color / 2;
	while (ray->draw_start <= 0 && ray->draw_end >= game->height && ++i <= game->height)
		mlx_pixel_put(game->mlx, game->mlx_win, \
				x, i, color);
	while (++i <= game->height)
	{
		if (i < ray->draw_start)
			mlx_pixel_put(game->mlx, game->mlx_win, \
				x, i, 0x108ED2);
		else if (i >= ray->draw_start && i <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (64 - 1);
			ray->tex_pos += ray->step;
			mlx_pixel_put(game->mlx, game->mlx_win, \
				x, i, game->map->n_texture[ray->tex_y][ray->tex_x]);
		}
		else
			mlx_pixel_put(game->mlx, game->mlx_win, \
				x, i, 0xffe3ab);
	}
}

void	raycasting(t_game *game)
{
	int			x;
	t_player	*pl;
	t_raycast	*ray;

	pl = game->pl;
	ray = game->ray;
	x = -1;
	while (++x < game->width)
	{
		init_var(game);
		ray->camera_x = 2 * x / (double)(game->width) - 1;
		ray->raydir_x = pl->pldir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = pl->pldir_y + ray->plane_y * ray->camera_x;
		if (ray->raydir_x == 0)
			ray->raydir_x = 1e30;
		else
			ray->delta_x = sqrt(1 + pow(ray->raydir_y, 2) / pow(ray->raydir_x, 2));
		if (ray->raydir_y == 0)
			ray->raydir_y = 1e30;
		else
			ray->delta_y = sqrt(1 + pow(ray->raydir_x, 2) / pow(ray->raydir_y, 2));

		//calculando step e distancia dos sides
		if (ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->side_x = (pl->pl_x - ray->map_x) * ray->delta_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_x = (ray->map_x + 1.0 - pl->pl_x) * ray->delta_x;
		}
		if (ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->side_y = (pl->pl_y - ray->map_y) * ray->delta_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_y = (ray->map_y + 1.0 - pl->pl_y) * ray->delta_y;
		}
		//iniciando DDA
		while (ray->hit == 0)
		{
			//pular para outro quadrado do mapa, para o X ou para o Y
			if (ray->side_x < ray->side_y)
			{
				ray->side_x += ray->delta_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_y += ray->delta_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			//Checar para ver se o raio atingiu 
			if (game->map->map[ray->map_x][ray->map_y] != '0')
				ray->hit = 1;
		}
		//Calculando a distancia projetada na direção da camera
		if (ray->side == 0) 
			ray->camera_wall = (ray->side_x - ray->delta_x);
		else
			ray->camera_wall = (ray->side_y - ray->delta_y);
		//Calculate height of line to draw on screen
		ray->line_height = (int)(game->height / ray->camera_wall);
		//calculate lowest and highest pixel to fill in current stripe
		ray->draw_start = (-1 * ray->line_height) / 2 + game->height / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + game->height / 2;
		if (ray->draw_end >= game->height)
			ray->draw_end = game->height - 1;

		if (ray->side == 0)
		{
			if (ray->raydir_x < 0)
				ray->tex_id = 0;
			else
				ray->tex_id = 1;
		}
		else
		{
			if (ray->raydir_y < 0)
				ray->tex_id = 2;
			else
				ray->tex_id = 3;
		}

		if (ray->side == 0)
			ray->wall_x = pl->pl_y + ray->camera_wall * ray->raydir_y;
		else
			ray->wall_x = pl->pl_x + ray->camera_wall * ray->raydir_x;
		ray->wall_x -= floor(ray->wall_x);

		ray->tex_x = (int)(ray->wall_x * 64);
		if ((ray->side == 0 && ray->raydir_x > 0) || (ray->side == 1 && ray->raydir_y < 0))
			ray->tex_x = 64 - ray->tex_x - 1;

		ray->step = 64 / (double)ray->line_height;
		ray->tex_pos = (ray->draw_start - game->height / 2 + ray->line_height / 2) * ray->step;

		ver_line(x, game);
	}
}