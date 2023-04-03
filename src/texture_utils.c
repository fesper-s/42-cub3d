/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:22:18 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/03 15:07:42 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**convert_texture(char **texture_line, char **hex_color, int i, int j)
{
	int		**texture;
	char	*texture_char;
	char	**buffer;

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

int	rgb_to_hex(char *rgb)
{
	char	**buffer;
	int		*rgb_value;
	int		hex_value;
	int		i;

	rgb_value = malloc(3 * sizeof(int));
	buffer = ft_split(rgb, ',');
	i = -1;
	while (++i < 3)
		rgb_value[i] = ft_atoi(buffer[i]);
	hex_value = (rgb_value[0] << 16) | (rgb_value[1] << 8) | rgb_value[2];
	free(rgb_value);
	return (hex_value);
}