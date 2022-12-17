/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:21:56 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/13 14:55:25 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static	void ft_pixel_calc_north(t_cub *cub, t_ray *ray)
{
	if (ray->direction == NE)
	{
		ray->floor_p->pixel_x = ray->offset_x
			- (cos(ray->angle) * ray->floor_p->floor_dist);
		ray->floor_p->pixel_y = ray->offset_y
			- (sin(ray->angle) * ray->floor_p->floor_dist);
	}
	if (ray->direction == NW)
	{
		ray->floor_p->pixel_x = ray->offset_x
			+ (cos(ray->angle) * ray->floor_p->floor_dist);
		ray->floor_p->pixel_y = ray->offset_y
			- (sin(ray->angle) * ray->floor_p->floor_dist);
	}
	(void)cub;
}

static	void ft_pixel_calc_south(t_cub *cub, t_ray *ray)
{
	if (ray->direction == SW)
	{
		ray->floor_p->pixel_x = ray->offset_x
			+ (cos(ray->angle) * ray->floor_p->floor_dist);
		ray->floor_p->pixel_y = ray->offset_y
			+ (sin(ray->angle) * ray->floor_p->floor_dist);
	}
	if (ray->direction == SE)
	{
		ray->floor_p->pixel_x = ray->offset_x
			- (cos(ray->angle) * ray->floor_p->floor_dist);
		ray->floor_p->pixel_y = ray->offset_y
			+ (sin(ray->angle) * ray->floor_p->floor_dist);
	}
	(void)cub;
}

static	void ft_param_calc(t_cub *cub, t_ray *ray, int j, float dist)
{
	// ray->floor_p->y_offset_px = j - cub->mdata->screen[1] * 0.5;
	ray->floor_p->y_offset_px = j - (cub->mdata->screen[1] >> 1);		//// using bitshifting instead of division
	ray->floor_p->y_offset = ray->floor_p->y_offset_px / ray->wall_height;
	ray->floor_p->floor_angle = ray->floor_p->y_offset / dist;
	ray->floor_p->floor_dist = ((ray->wall_height * 0.5)
			/ tan(ray->floor_p->floor_angle) / ray->wall_height);
	ft_pixel_calc_north(cub, ray);
	ft_pixel_calc_south(cub, ray);
	ray->floor_p->pixel_x = (floor(ray->floor_p->pixel_x)
			- ray->floor_p->pixel_x + 1) * cub->floor->width[0];
	ray->floor_p->pixel_y = (floor(ray->floor_p->pixel_y)
			- ray->floor_p->pixel_y + 1) * cub->floor->height[0];
}

void	ft_render_floor(t_cub *cub, t_ray *ray, int i, int j, float dist)
{
	int		pix_color = 0;

	// pthread_mutex_lock(&cub->mutex);
	ft_param_calc(cub, ray, j, dist);
	if (ray->direction == SW)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)ray->floor_p->pixel_x, (int)(cub->floor->height[0]
					- ray->floor_p->pixel_y));
	if (ray->direction == NE)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)(cub->floor->width[0] - ray->floor_p->pixel_x),
				(int)ray->floor_p->pixel_y);
	if (ray->direction == SE)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)(cub->floor->width[0] - ray->floor_p->pixel_x),
				(int)(cub->floor->height[0] - ray->floor_p->pixel_y));
	if (ray->direction == NW)
		pix_color = ft_get_color_from_texture(cub->floor,
				(int)ray->floor_p->pixel_x, (int)ray->floor_p->pixel_y);
	// pthread_mutex_unlock(&cub->mutex);
	if (cub->light == -1)
		pix_color = ft_shade_color(pix_color, ft_flashlight(cub, ray->floor_p->floor_dist * 1.1, i, j, 0));
	ft_multi_pixel_put(cub, cub->img, i, j, ft_downscaling(cub, i, j), pix_color);
}
