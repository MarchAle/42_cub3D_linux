/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:38:12 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 11:01:27 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_is_wall(t_cub *cub, int x, int y, int size)
{
	if (cub->map[y / size][x / size] == '1')
		return (1);
	else if (cub->map[y / size][x / size] == '0'
		|| cub->map[y / size][x / size] == 'N'
		|| cub->map[y / size][x / size] == 'S'
		|| cub->map[y / size][x / size] == 'E'
		|| cub->map[y / size][x / size] == 'W')
		return (0);
	else
		return (-1);
}

void	ft_mini_map(t_cub *cub)
{
	int	x;
	int	y;
	int	i;
	int	size;

	size = MINIMAP_SIZE / cub->mdata->max_size;
	y = -1;
	while (y++ < (int)ft_strlen2d(cub->map) * size)
	{
		x = -1;
		while (cub->map[y / size] && x++ < (int)ft_strlen(cub->map[y / size])
			* size)
		{
			if (ft_is_wall(cub, x, y, size) == 1)
				my_mlx_pixel_put(cub->img, x + 30, y + 80, 0x1a1718);
			else if (ft_is_wall(cub, x, y, size) == 0)
				my_mlx_pixel_put(cub->img, x + 30, y + 80, 0x8c8789);
		}
	}
	i = cub->mdata->screen[0] / 3;
	while (i-- > 0)
		ft_raycast(i * 3, cub, TRUE, size);
}
