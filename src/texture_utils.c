/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:22:18 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/03 14:15:26 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
