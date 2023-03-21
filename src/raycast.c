/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:15:23 by gussoare          #+#    #+#             */
/*   Updated: 2023/03/21 14:15:05 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ver_line(int x, t_game *game)
{
	t_raycast *ray;
	
	ray = game->ray;
	while (ray->draw_start <= ray->draw_end)
	{
		if (ray->side == 1)
			mlx_pixel_put(game->mlx, game->mlx_win, ray->draw_start, x, 0xFF5555 / 2);
		else
			mlx_pixel_put(game->mlx, game->mlx_win, ray->draw_start, x, 0xFF5555);
		ray->draw_start++;
	}
}


void raycasting(t_game *game)
{
	int	x;
	t_player *pl;
	t_raycast *ray;

	pl = game->pl;
	ray = game->ray;
	while (1)
	{
		x = -1;
		while (++x < game->width)
		{
			ray->camera_x = 2 * x / (game->width) - 1;
			ray->raydir_x = pl->pl_x + ray->plane_x * ray->camera_x;
			ray->raydir_y = pl->pl_y + ray->plane_y * ray->camera_x;
			if (ray->raydir_x == 0)
				ray->raydir_x = 1e30;
			if (ray->raydir_y == 0)
				ray->raydir_y = 1e30;
			ray->delta_x = sqrt(1 + pow(ray->raydir_y, 2) / pow(ray->raydir_x, 2));
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
				printf("ray->map_x--> %d\n", ray->map_x);
				printf("ray->map_y--> %d\n", ray->map_y);
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
			ray->draw_start = -ray->line_height / 2 + game->height / 2;
			if(ray->draw_start < 0)
				ray->draw_start = 0;
			ray->draw_end = ray->line_height / 2 + game->height / 2;
			if(ray->draw_end >= game->height)
				ray->draw_end = game->height - 1;
			ver_line(x, game);
		}
		break;
	}
}