/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:21:56 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 15:38:56 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void static	ft_pixel_calc_north(t_cub *cub)
{
	if (cub->ray->direction == NE)
	{
		cub->floor_p->pixel_x = cub->player->offset_x
			- (cos(cub->ray->angle) * cub->floor_p->floor_dist);
		cub->floor_p->pixel_y = cub->player->offset_y
			- (sin(cub->ray->angle) * cub->floor_p->floor_dist);
	}
	if (cub->ray->direction == NW)
	{
		cub->floor_p->pixel_x = cub->player->offset_x
			+ (cos(cub->ray->angle) * cub->floor_p->floor_dist);
		cub->floor_p->pixel_y = cub->player->offset_y
			- (sin(cub->ray->angle) * cub->floor_p->floor_dist);
	}
}

void static	ft_pixel_calc_south(t_cub *cub)
{
	if (cub->ray->direction == SW)
	{
		cub->floor_p->pixel_x = cub->player->offset_x
			+ (cos(cub->ray->angle) * cub->floor_p->floor_dist);
		cub->floor_p->pixel_y = cub->player->offset_y
			+ (sin(cub->ray->angle) * cub->floor_p->floor_dist);
	}
	if (cub->ray->direction == SE)
	{
		cub->floor_p->pixel_x = cub->player->offset_x
			- (cos(cub->ray->angle) * cub->floor_p->floor_dist);
		cub->floor_p->pixel_y = cub->player->offset_y
			+ (sin(cub->ray->angle) * cub->floor_p->floor_dist);
	}
}

void static	ft_param_calc(t_cub *cub, int j, float dist)
{
	cub->floor_p->y_offset_px = j - cub->mdata->screen[1] * 0.5;
	cub->floor_p->y_offset = cub->floor_p->y_offset_px / cub->ray->wall_height;
	cub->floor_p->floor_angle = cub->floor_p->y_offset / dist;
	cub->floor_p->floor_dist = ((cub->ray->wall_height * 0.5)
			/ tan(cub->floor_p->floor_angle) / cub->ray->wall_height);
	ft_pixel_calc_north(cub);
	ft_pixel_calc_south(cub);
	cub->floor_p->pixel_x = (floor(cub->floor_p->pixel_x)
			- cub->floor_p->pixel_x + 1) * cub->floor->width[0];
	cub->floor_p->pixel_y = (floor(cub->floor_p->pixel_y)
			- cub->floor_p->pixel_y + 1) * cub->floor->height[0];
}

int	ft_render_floor(t_cub *cub, int i, int j, float dist)
{
	int		pix_color;

	ft_param_calc(cub, j, dist);
	if (cub->ray->direction == SW)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)cub->floor_p->pixel_x, (int)(cub->floor->height[0]
					- cub->floor_p->pixel_y));
	if (cub->ray->direction == NE)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)(cub->floor->width[0] - cub->floor_p->pixel_x),
				(int)cub->floor_p->pixel_y);
	if (cub->ray->direction == SE)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)(cub->floor->width[0] - cub->floor_p->pixel_x),
				(int)(cub->floor->height[0] - cub->floor_p->pixel_y));
	if (cub->ray->direction == NW)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)cub->floor_p->pixel_x, (int)cub->floor_p->pixel_y);
	pix_color = ft_shade_color(pix_color, cub->floor_p->floor_dist);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
	my_mlx_pixel_put(cub->img, i, j + 1, pix_color);
	my_mlx_pixel_put(cub->img, i + 1, j + 1, pix_color);
	my_mlx_pixel_put(cub->img, i + 1, j, pix_color);
	j++;
	return (j);
}
