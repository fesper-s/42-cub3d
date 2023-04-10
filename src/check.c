/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:24:30 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/10 13:02:13 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_sprites(t_map *map)
{
	if (!map->north || map->north[0] == 0)
		return (exit_error("Empty north path"), 0);
	else if (!map->south || map->south[0] == 0)
		return (exit_error("Empty south path"), 0);
	else if (!map->east || map->east[0] == 0)
		return (exit_error("Empty east path"), 0);
	else if (!map->west || map->west[0] == 0)
		return (exit_error("Empty west path"), 0);
	else if (!map->floor || map->floor[0] == 0)
		return (exit_error("Empty floor color"), 0);
	else if (!map->ceiling || map->ceiling[0] == 0)
		return (exit_error("Empty ceiling color"), 0);
	return (1);
}
