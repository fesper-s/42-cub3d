/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:42:08 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/03 11:22:38 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * 8);
	i = -1;
	j = -1;
	while (line[++i])
	{
		while ((line[i] == ' ' || line[i] == 'c' || line[i] == '#' || \
			line[i] == '\"' || line[i] == ',') && i != 1)
			i++;
		new_line[++j] = line[i];
	}
	new_line[j + 1] = 0;
	free(line);
	return (new_line);
}

char	**get_hex_color(int fd)
{
	char	**hex_color;
	char	*line;
	char	*hex_line;
	char	*aux;

	hex_line = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "/* columns rows colors chars-per-pixel */", 41))
		{
			line = get_next_line(fd);
			line = get_next_line(fd);
			while (ft_strncmp(line, "/* pixels */", 12))
			{
				line = check_line(line);
				aux = ft_strjoin(hex_line, line);
				free(hex_line);
				hex_line = ft_strdup(aux);
				free(aux);
				free(line);
				line = get_next_line(fd);
			}
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	hex_color = ft_split(hex_line, '\n');
	free(hex_line);
	return (hex_color);
}

char	*check_texture_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	if (line[ft_strlen(line) - 1] == ',')
		new_line = malloc(sizeof(char) * (ft_strlen(line) - 3 + 1));
	else
		new_line = malloc(sizeof(char) * (ft_strlen(line) - 2 + 1));
	i = -1;
	j = -1;
	while (line[++i])
	{
		while (i == 0 || i == (int) ft_strlen(line) - 2 || \
			(i == (int) ft_strlen(line) - 3 && \
			line[ft_strlen(line) - 2] == ','))
			i++;
		new_line[++j] = line[i];
	}
	new_line[j + 1] = 0;
	free(line);
	return (new_line);
}

char	**get_texture_line(int fd)
{
	char	*line;
	char	*aux;
	char	*buffer;
	char	**texture_line;

	buffer = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "/* pixels */", 12))
		{
			free(line);
			line = get_next_line(fd);
			while (ft_strncmp(line, "};", 2))
			{
				line = check_texture_line(line);
				aux = ft_strjoin(buffer, line);
				free(buffer);
				buffer = ft_strdup(aux);
				free(aux);
				free(line);
				line = get_next_line(fd);
			}
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	texture_line = ft_split(buffer, '\n');
	free(buffer);
	return (texture_line);
}

int	**convert_texture(char **texture_line, char **hex_color)
{
	int		**texture;
	char	*texture_char;
	char	**buffer;
	int		i;
	int		j;

	i = -1;
	texture = malloc(sizeof(int *) * 64);
	buffer = hex_color;
	while (*texture_line)
	{
		texture[++i] = malloc(sizeof(int) * 64);
		texture_char = *texture_line;
		j = -1;
		while (*texture_char)
		{
			if (j < 63)
				j++;
			hex_color = buffer;
			while (*hex_color)
			{
				if (*texture_char == *hex_color[0])
					texture[i][j] = ft_atoi_base(&(*hex_color)[1], 16);
				hex_color++;
			}
			texture_char++;
		}
		texture_line++;
	}
	return (texture);
}
