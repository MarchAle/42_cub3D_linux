/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:38:57 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:30:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int static	ft_pix_color_calc(t_cub *cub, int j, t_texture *tex)
{
	int	color;

	cub->ray->texture_offset_y = (float)((j
				- ((cub->mdata->screen[1] - cub->ray->wall_height) / 2))
			/ (cub->ray->wall_height) * tex->height[0]);
	color = ft_get_color_from_texture(tex, (int)cub->ray->texture_offset_x,
			(int)cub->ray->texture_offset_y);
	return (color);
}

void	ft_render_wall(t_cub *cub, int i, int j, float dist)
{
	int	pix_color;

	if (cub->ray->wall_orientation == N)
		pix_color = ft_pix_color_calc(cub, j, cub->north);
	else if (cub->ray->wall_orientation == S)
		pix_color = ft_pix_color_calc(cub, j, cub->south);
	else if (cub->ray->wall_orientation == E)
		pix_color = ft_pix_color_calc(cub, j, cub->east);
	else
		pix_color = ft_pix_color_calc(cub, j, cub->west);
	pix_color = ft_shade_color(pix_color, dist);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
}
