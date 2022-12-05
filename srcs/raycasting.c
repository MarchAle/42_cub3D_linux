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

void	ft_offset_init(t_cub *cub)
{
	cub->player->offset_x = cub->player->x - floor(cub->player->x);
	if (cub->ray->direction == NE || cub->ray->direction == SE)
		cub->player->offset_x = 1 - cub->player->offset_x;
	cub->player->offset_y = cub->player->y - floor(cub->player->y);
	if (cub->ray->direction == SW || cub->ray->direction == SE)
		cub->player->offset_y = 1 - cub->player->offset_y;
}

// float	ft_angleCalculation2(int i, t_cub *cub)
// {
// 	float a = sqrtf(pow(i, 2) + cub->calc->powd - (2 * i * cub->calc->d * cub->calc->cosalpha));
// 	float angle = asin(cub->calc->sinalpha * i / a);
// 	cub->ray->angle_player = cub->calc->fovHalf - angle;
// 	return (angle);
// }

float	ft_raycast(int i, t_cub *cub, int print_ray, int minimap_size)
{
	float	dist;
	float	tmp_dist;
	int		ray_color;

	tmp_dist = 0;
	// cub->ray->angle = cub->player->orient - cub->calc->fovHalf + ft_angleCalculation2(i, cub);
	// printf("%f\n", cub->ray->angle);
	cub->ray->angle = cub->player->orient - cub->calc->fovHalf + cub->angles[i];
	cub->ray->angle_player = cub->calc->fovHalf - cub->angles[i];
	// printf("%f\n", cub->ray->angle);
	ft_trigo_angle(cub);
	ft_get_direction(cub);
	ft_offset_init(cub);
	dist = ft_dist_to_wall(cub);
	if (print_ray == TRUE)
	{
		while (tmp_dist < dist && tmp_dist < 8)
		{
			ray_color = 0x0D062B;
			cub->ray->x = cub->player->x + tmp_dist * cub->calc->cosAngle;
			cub->ray->y = cub->player->y - tmp_dist * cub->calc->sinAngle;
			ray_color = ft_fade_color(ray_color, tmp_dist);
			my_mlx_pixel_put(cub->img, cub->ray->x * minimap_size + 30,
				cub->ray->y * minimap_size + 80, ray_color);
			tmp_dist += 0.08;
		}
	}
	return (dist);
}

void	ft_get_direction(t_cub *cub)
{
	if (cub->ray->angle <= -cub->calc->piHalf && cub->ray->angle >= -M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= cub->calc->piHalf && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= cub->calc->piHalf)
		cub->ray->direction = NE;
	else if (cub->ray->angle > -cub->calc->piHalf && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > -M_PI && cub->ray->angle <= -cub->calc->piHalf)
		cub->ray->direction = SW;
	else if (cub->ray->angle > M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle < -M_PI)
		cub->ray->direction = NW;
}
