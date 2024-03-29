/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:24:30 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/18 10:35:32 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_sprites(t_map *map)
{
	if (!map->north || map->north[0] == 0)
		exit_error("Empty north path");
	else if (!map->south || map->south[0] == 0)
		exit_error("Empty south path");
	else if (!map->east || map->east[0] == 0)
		exit_error("Empty east path");
	else if (!map->west || map->west[0] == 0)
		exit_error("Empty west path");
	else if (!map->floor || map->floor[0] == 0)
		exit_error("Empty floor color");
	else if (!map->ceiling || map->ceiling[0] == 0)
		exit_error("Empty ceiling color");
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		exit_error("Invalid type of file");
	init_map(map);
	read_map(path, map);
	return (0);
}
