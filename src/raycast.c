/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:15:23 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/05 14:09:55 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pixel_put(t_game *game, int x, int y, int color)
{
	t_image	*img;
	int		pixel;

	img = game->img;
	if (y >= game->height || x >= game->width || y < 0 || x < 0)
		return ;
	pixel = (y * img->line_len) + (x * (img->bpp / 8));
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
}

void	img_paste_pixel(t_game *game, int x, int y, int pixel)
{
	t_image	*img;
	char	*dst;

	img = game->img;
	if (y >= game->height || x >= game->width || y < 0 || x < 0)
		return ;
	dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)dst = pixel;
}

void	ver_line(int x, t_game *game, int **tex)
{
	t_raycast	*ray;
	int			i;

	i = -1;
	ray = game->ray;
	while (++i < game->height)
	{
		if (i < ray->draw_start)
			img_pixel_put(game, game->width - x - 1, \
				i, game->map->c_color);
		else if (i >= ray->draw_start && i <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (64 - 1);
			ray->tex_pos += ray->step;
			img_paste_pixel(game, game->width - 1 - x, \
				i, tex[ray->tex_y][ray->tex_x]);
		}
		else
			img_pixel_put(game, game->width - x - 1, \
				i, game->map->f_color);
	}
}

void	step_and_side_calc(t_game *game)
{
	t_raycast	*ray;
	t_player	*pl;

	ray = game->ray;
	pl = game->pl;
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
}

void	dda(t_game *game)
{
	t_raycast	*ray;

	ray = game->ray;
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
		//Calculando a distancia projetada na direção da camera
		if (ray->side == 0) 
			ray->camera_wall = (ray->side_x - ray->delta_x);
		else
			ray->camera_wall = (ray->side_y - ray->delta_y);
	}
}

void	get_line_position(t_game *game)
{
	t_raycast	*ray;

	ray = game->ray;
	//Calculate height of line to draw on screen
	ray->line_height = (int)(game->height / ray->camera_wall);
	//calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = (-1 * ray->line_height) / 2 + game->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->height / 2;
	if (ray->draw_end >= game->height)
		ray->draw_end = game->height - 1;
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
		init_raycast(game, x);
		step_and_side_calc(game);
		dda(game);
		get_line_position(game);

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
		if (ray->tex_id == 0)
			ver_line(x, game, game->map->n_texture);
		else if (ray->tex_id == 1)
			ver_line(x, game, game->map->s_texture);
		else if (ray->tex_id == 2)
			ver_line(x, game, game->map->e_texture);
		else
			ver_line(x, game, game->map->w_texture);


	}
}