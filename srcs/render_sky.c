/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:01:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 15:38:32 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void static	ft_param_calc(t_cub *cub, int j, float dist)
{
	cub->sky_p->y_offset_px = (cub->mdata->screen[1] * 0.5) - j;
	cub->sky_p->y_offset = cub->sky_p->y_offset_px / cub->ray->wall_height;
	cub->sky_p->floor_angle = cub->sky_p->y_offset / dist;
	cub->sky_p->floor_dist = ((cub->ray->wall_height * 12)
			/ tan(cub->sky_p->floor_angle) / cub->ray->wall_height);
	cub->sky_p->pixel_x = cub->player->x + (cos(cub->ray->angle)
			* cub->sky_p->floor_dist);
	cub->sky_p->pixel_y = cub->player->y - (sin(cub->ray->angle)
			* cub->sky_p->floor_dist);
}

void static	ft_pixel_adjustment(t_cub *cub)
{
	if (cub->sky_p->pixel_x < 0)
		cub->sky_p->pixel_x *= -1;
	while (cub->sky_p->pixel_x > 50)
		cub->sky_p->pixel_x -= 50;
	if (cub->sky_p->pixel_x < 0)
		cub->sky_p->pixel_x *= -1;
	cub->sky_p->pixel_x = cub->sky_p->pixel_x / 50 * cub->sky->width[0];
	if (cub->sky_p->pixel_y < 0)
		cub->sky_p->pixel_y *= -1;
	while (cub->sky_p->pixel_y > 50)
		cub->sky_p->pixel_y -= 50;
	if (cub->sky_p->pixel_y < 0)
		cub->sky_p->pixel_y *= -1;
	cub->sky_p->pixel_y = cub->sky_p->pixel_y / 50 * cub->sky->height[0];
}

int	ft_render_sky(t_cub *cub, int i, int j, float dist)
{
	int		pix_color;

	ft_param_calc(cub, j, dist);
	ft_pixel_adjustment(cub);
	pix_color = ft_get_color_from_texture(cub->sky,
			(int)cub->sky_p->pixel_x, (int)cub->sky_p->pixel_y);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
	my_mlx_pixel_put(cub->img, i, j + 1, pix_color);
	my_mlx_pixel_put(cub->img, i + 1, j + 1, pix_color);
	my_mlx_pixel_put(cub->img, i + 1, j, pix_color);
	j++;
	return (j);
}
