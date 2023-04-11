/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/11 08:58:03 by gussoare         ###   ########.fr       */
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
		exit_error("File doesn't exist");
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

int	grand_line(char **str)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((int)ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
	}
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
		exit_error("File doesn't exist");
	i = -1;
	j = 0;
	while (++i < map_len)
		get_map_info(fd, map, &j);
	map->map[j] = 0;
	close(fd);
	return (0);
}

void	insert_fill_line(t_map *map, char ***b_map)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 1;
	while (map->map[++i])
	{
		(*b_map)[j] = malloc((grand_line(map->map) + 3) * sizeof(char));
		(*b_map)[j][0] = '3';
		ft_strlcat((*b_map)[j], map->map[i], grand_line(map->map) + 2);
		k = ft_strlen(map->map[i]);
		while (++k < grand_line(map->map) + 2)
			(*b_map)[j][k] = '3';
		(*b_map)[j][k] = 0;
		j++;
	}
}

void	map_validation(t_map *map)
{
	char	**b_map;
	int		len;
	int		line_len;
	int		i;
	int		k;

	line_len = grand_line(map->map);
	printf("antes do len\n");
	len = 0;
	while (map->map[len])
		len++;
	b_map = malloc((len + 3) * sizeof(char *));

	printf("antes da primeira linha\n");
	b_map[0] = malloc(sizeof(char) * (line_len + 3));
	k = -1;
	while (++k < line_len + 2)
		b_map[0][k] = '3';
	b_map[0][k] = 0;

	printf("antes de copiar o mapa\n");
	insert_fill_line(map, &b_map);

	printf("antes da ultima linha\n");
	b_map[len + 1] = malloc(sizeof(char) * (line_len + 3));
	k = -1;
	while (++k < line_len + 2)
		b_map[len + 1][k] = '3';
	b_map[len + 1][k] = 0;

	printf("antes de printar o mapa\n");
	i = -1;
	while (b_map[++i])
		printf("%s\n", b_map[i]);
}


int	read_map(char *path, t_map *map)
{
	int		map_len;
	int		i;

	i = -1;
	map_len = maplen(path);
	map->map = malloc(sizeof(char *) * (map_len + 1 - 6));
	assign_map(map, path, map_len);
	if (!check_sprites(map))
		return (0);
	while (map->map[++i])
		replace_char(map->map[i], ' ', '3');
	map_validation(map);
	return (1);
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		exit_error("Invalid type of file");
	init_map(map);
	read_map(path, map);
	return (0);
}
