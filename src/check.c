/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:24:30 by gussoare          #+#    #+#             */
/*   Updated: 2023/03/14 11:44:07 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_sprites(t_map *map)
{
	if (!map->north || map->north[0] == 0)
		return (print_error("Empty north parth"), 0);
	else if (!map->south || map->south[0] == 0)
		return (print_error("Empty south parth"), 0);
	else if (!map->east || map->east[0] == 0)
		return (print_error("Empty east parth"), 0);
	else if (!map->west || map->west[0] == 0)
		return (print_error("Empty west parth"), 0);
	else if (!map->floor || map->floor[0] == 0)
		return (print_error("Empty floor color"), 0);
	else if (!map->ceiling || map->ceiling[0] == 0)
		return (print_error("Empty ceiling color"), 0);
	return (1);
}
