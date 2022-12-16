/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:02:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 11:01:09 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_offset_init(t_cub *cub, t_ray *ray)
{
	cub->player->offset_x = cub->player->x - floor(cub->player->x);
	if (ray->direction == NE || ray->direction == SE)
		cub->player->offset_x = 1 - cub->player->offset_x;
	cub->player->offset_y = cub->player->y - floor(cub->player->y);
	if (ray->direction == SW || ray->direction == SE)
		cub->player->offset_y = 1 - cub->player->offset_y;
}

// float	ft_angleCalculation2(int i, t_cub *cub)
// {
// 	float a = sqrtf(pow(i, 2) + cub->calc->powd - (2 * i * cub->calc->d * cub->calc->cosalpha));
// 	float angle = asin(cub->calc->sinalpha * i / a);
// 	cub->ray->angle_player = cub->calc->fovHalf - angle;
// 	return (angle);
// }

float	ft_raycast(int i, t_cub *cub, t_ray *ray, int print_ray, int minimap_size)
{
	float	dist;
	float	tmp_dist;
	int		ray_color;

	tmp_dist = 0;
	// ray->angle = cub->player->orient - cub->calc->fovHalf + ft_angleCalculation2(i, cub);
	// printf("%f\n", ray->angle);
	ray->angle = cub->player->orient - cub->calc->fovHalf + cub->angles[i];
	ray->angle_player = cub->calc->fovHalf - cub->angles[i];
	// printf("%f\n", ray->angle);
	ft_trigo_angle(ray);
	ft_get_direction(cub, ray);
	//////////// MUTEX lock
	ft_offset_init(cub, ray);
	//////////// MUTEX unlock
	dist = ft_dist_to_wall(cub, ray);
	if (print_ray == TRUE)
	{
		while (tmp_dist < dist && tmp_dist < 8)
		{
			ray_color = 0x0D062B;
			ray->x = cub->player->x + tmp_dist * ray->cosAngle;
			ray->y = cub->player->y - tmp_dist * ray->sinAngle;
			ray_color = ft_fade_color(ray_color, tmp_dist);
			my_mlx_pixel_put(cub->img, ray->x * minimap_size + 30,
				ray->y * minimap_size + 80, ray_color);
			tmp_dist += 0.08;
		}
	}
	return (dist);
}

void	ft_get_direction(t_cub *cub, t_ray *ray)
{
	if (ray->angle <= -cub->calc->piHalf && ray->angle >= -M_PI)
		ray->direction = SW;
	else if (ray->angle >= cub->calc->piHalf && ray->angle <= M_PI)
		ray->direction = NW;
	else if (ray->angle >= 0 && ray->angle <= cub->calc->piHalf)
		ray->direction = NE;
	else if (ray->angle > -cub->calc->piHalf && ray->angle <= 0)
		ray->direction = SE;
	else if (ray->angle > -M_PI && ray->angle <= -cub->calc->piHalf)
		ray->direction = SW;
	else if (ray->angle > M_PI)
		ray->direction = SW;
	else if (ray->angle < -M_PI)
		ray->direction = NW;
}
