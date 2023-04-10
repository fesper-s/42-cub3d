/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/10 11:10:09 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	maplen(char *path)
{
	int		len;
	int		fd;
	char	*aux;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	len = 0;
	aux = get_next_line(fd);
	while (aux)
	{
		free(aux);
		aux = get_next_line(fd);
		len++;
	}
	free(aux);
	close(fd);
	return (len);
}

void	get_map_info(int fd, t_map *map, int *j)
{
	char	*aux;
	char	*buffer;

	aux = get_next_line(fd);
	buffer = ft_strtrim(aux, "\n");
	if (!ft_strncmp(buffer, "NO ", 3))
		map->north = ft_strtrim(buffer + 2, " ");
	else if (!ft_strncmp(buffer, "SO ", 3))
		map->south = ft_strtrim(buffer + 2, " ");
	else if (!ft_strncmp(buffer, "EA ", 3))
		map->east = ft_strtrim(buffer + 2, " ");
	else if (!ft_strncmp(buffer, "WE ", 3))
		map->west = ft_strtrim(buffer + 2, " ");
	else if (!ft_strncmp(buffer, "F ", 2))
		map->floor = ft_strtrim(buffer + 1, " ");
	else if (!ft_strncmp(buffer, "C ", 2))
		map->ceiling = ft_strtrim(buffer + 1, " ");
	else if (ft_strlen(buffer) && buffer[0])
		map->map[(*j)++] = ft_strdup(buffer);
	free(buffer);
	free(aux);
}

int	assign_map(t_map *map, char *path, int map_len)
{
	int		i;
	int		j;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	i = -1;
	j = 0;
	while (++i < map_len)
		get_map_info(fd, map, &j);
	map->map[j] = 0;
	close(fd);
	return (0);
}

int	read_map(char *path, t_map *map)
{
	int		map_len;
	//realizar uma função de checagem de mapa e tirar a função replace_char
	int		i = -1;

	map_len = maplen(path);
	map->map = malloc(sizeof(char *) * (map_len + 1 - 6));
	assign_map(map, path, map_len);
	if (!check_sprites(map))
		return (0);
	while (map->map[++i])
		replace_char(map->map[i], ' ', '1');
	return (1);
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		return (print_error("Invalid type of file"));
	read_map(path, map);
	return (0);
}
