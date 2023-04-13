/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:21:08 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/13 08:42:56 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_players(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (ft_strchr("NSEO", map->map[i][j]))
				count++;
		}
	}
	if (count > 1)
		exit_error("There's more than one player inside map");
	else if (count <= 0)
		exit_error("No player found on map");
}

void	map_validation(t_map *map)
{
	char	**b_map;
	int		len;
	int		line_len;
	int		i;

	line_len = grand_line(map->map);
	len = 0;
	while (map->map[len])
		len++;
	b_map = malloc((len + 3) * sizeof(char *));
	b_map[0] = malloc(sizeof(char) * (line_len + 3));
	i = -1;
	while (++i < line_len + 2)
		b_map[0][i] = '3';
	b_map[0][i] = 0;
	insert_fill_line(map, &b_map);
	b_map[len + 1] = malloc(sizeof(char) * (line_len + 3));
	i = -1;
	while (++i < line_len + 2)
		b_map[len + 1][i] = '3';
	b_map[len + 1][i] = 0;
	b_map[len + 2] = 0;
	check_breach(b_map);
	free_charpp(b_map);
}

void	check_map_elements(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (!ft_strchr("NSEO10 ", map->map[i][j]))
				exit_error("Invalid element inside map");
		}
	}
	count_players(map);
}

void	check_breach(char **b_map)
{
	int	i;
	int	j;

	i = -1;
	while (b_map[++i])
	{
		j = -1;
		while (b_map[i][++j])
		{
			if (b_map[i][j] == '0' || ft_strchr("NSEW", b_map[i][j]))
			{
				if (b_map[i][j + 1] == '3' || b_map[i][j - 1] == '3' || \
					b_map[i + 1][j] == '3' || b_map[i - 1][j] == '3')
				{
					free_charpp(b_map);
					exit_error("Breached map");
				}
			}
		}
	}
}
