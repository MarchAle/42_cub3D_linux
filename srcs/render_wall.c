/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:38:57 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/13 14:54:44 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int ft_pix_color_calc(t_cub *cub, t_ray *ray, int j, t_texture *tex)
{
	int	color;

	ray->texture_offset_y = (float)((j
				- ((cub->mdata->screen[1] - ray->wall_height) / 2))
			/ (ray->wall_height) * tex->height[0]);
	color = ft_get_color_from_texture(tex, (int)ray->texture_offset_x,
			(int)ray->texture_offset_y);
	return (color);
}

void	ft_render_wall(t_cub *cub, t_ray *ray, int i, int j, float dist)
{
	int	pix_color;

	if (ray->wall_orientation == N)
		pix_color = ft_pix_color_calc(cub, ray, j, cub->north);
	else if (ray->wall_orientation == S)
		pix_color = ft_pix_color_calc(cub, ray, j, cub->south);
	else if (ray->wall_orientation == E)
		pix_color = ft_pix_color_calc(cub, ray, j, cub->east);
	else
		pix_color = ft_pix_color_calc(cub, ray, j, cub->west);
	if (cub->light == -1)
		pix_color = ft_shade_color(pix_color, ft_flashlight(cub, dist, i, j, WALL));
	ft_multi_pixel_put(cub, cub->img, i, j, ft_downscaling(cub, i, j), pix_color);
}
