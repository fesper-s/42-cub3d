/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:44:15 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/04 09:37:43 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_north_texture(t_map *map)
{
	int		fd;
	char	**hex_color;
	char	**texture_line;

	fd = open(map->north, O_RDONLY);
	if (fd == -1)
		exit_error("invalid texture file");
	hex_color = get_hex_color(fd);
	close(fd);
	fd = open(map->north, O_RDONLY);
	texture_line = get_texture_line(fd);
	close(fd);
	map->n_texture = convert_texture(texture_line, hex_color, -1, 0);
	free_charpp(hex_color);
	free_charpp(texture_line);
}

void	get_south_texture(t_map *map)
{
	int		fd;
	char	**hex_color;
	char	**texture_line;

	fd = open(map->south, O_RDONLY);
	if (fd == -1)
		exit_error("invalid texture file");
	hex_color = get_hex_color(fd);
	close(fd);
	fd = open(map->south, O_RDONLY);
	texture_line = get_texture_line(fd);
	close(fd);
	map->s_texture = convert_texture(texture_line, hex_color, -1, 0);
	free_charpp(hex_color);
	free_charpp(texture_line);
}

void	get_east_texture(t_map *map)
{
	int		fd;
	char	**hex_color;
	char	**texture_line;

	fd = open(map->east, O_RDONLY);
	if (fd == -1)
		exit_error("invalid texture file");
	hex_color = get_hex_color(fd);
	close(fd);
	fd = open(map->east, O_RDONLY);
	texture_line = get_texture_line(fd);
	close(fd);
	map->e_texture = convert_texture(texture_line, hex_color, -1, 0);
	free_charpp(hex_color);
	free_charpp(texture_line);
}

void	get_west_texture(t_map *map)
{
	int		fd;
	char	**hex_color;
	char	**texture_line;

	fd = open(map->west, O_RDONLY);
	if (fd == -1)
		exit_error("invalid texture file");
	hex_color = get_hex_color(fd);
	close(fd);
	fd = open(map->west, O_RDONLY);
	texture_line = get_texture_line(fd);
	close(fd);
	map->w_texture = convert_texture(texture_line, hex_color, -1, 0);
	free_charpp(hex_color);
	free_charpp(texture_line);
}

void	get_texture(t_map *map)
{
	get_north_texture(map);
	get_south_texture(map);
	get_east_texture(map);
	get_west_texture(map);
	map->f_color = rgb_to_hex(map->floor);
	map->c_color = rgb_to_hex(map->ceiling);
}
