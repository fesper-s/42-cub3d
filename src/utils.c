/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:54:44 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 09:01:25 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strrncmp(char *s1, char *s2, int len)
{
	int	size_s1;
	int size_s2;

	if (!len)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	while (len)
	{
		if (s1[size_s1] != s2[size_s2])
			return (s1[size_s1] - s2[size_s2]);
		size_s1--;
		size_s2--;
		len--;
	}
	return (0);
}
