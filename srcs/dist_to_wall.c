/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:34 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:24:30 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_nearest_wall_y(t_cub *cub, float *shortest_dist)
{
	if (cub->ray->direction == NW || cub->ray->direction == NE)
		ft_nearest_north_wall_y(cub, shortest_dist);
	else
		ft_nearest_south_wall_y(cub, shortest_dist);
	if (cub->ray->direction == NE)
		cub->ray->texture_offset_x = ((cos(cub->ray->angle) * *shortest_dist)
				- (cub->player->offset_x - 1)) * cub->north->width[0];
	if (cub->ray->direction == SE)
		cub->ray->texture_offset_x = ((cos(cub->ray->angle) * *shortest_dist)
				- (cub->player->offset_x - 1)) * cub->south->width[0];
	if (cub->ray->direction == NW)
		cub->ray->texture_offset_x = -(-cos(cub->ray->angle) * *shortest_dist
				- (floor(cub->player->offset_x) + (cub->player->offset_x
						- floor(cub->player->offset_x))))
			* cub->north->width[0];
	if (cub->ray->direction == SW)
		cub->ray->texture_offset_x = -(-cos(cub->ray->angle) * *shortest_dist
				- (floor(cub->player->offset_x) + (cub->player->offset_x
						- floor(cub->player->offset_x))))
			* cub->south->width[0];
}

void	ft_nearest_wall_x(t_cub *cub, float *shortest_dist)
{
	if (cub->ray->direction == NW || cub->ray->direction == NE)
		ft_nearest_north_wall_x(cub, shortest_dist);
	else
		ft_nearest_south_wall_x(cub, shortest_dist);
	if (cub->ray->direction == NE)
		cub->ray->texture_offset_x = ((sin(cub->ray->angle) * *shortest_dist)
				- (cub->player->offset_y - 1)) * cub->east->width[0];
	if (cub->ray->direction == NW)
		cub->ray->texture_offset_x = ((sin(cub->ray->angle) * *shortest_dist)
				- (cub->player->offset_y - 1)) * cub->west->width[0];
	if (cub->ray->direction == SE)
		cub->ray->texture_offset_x = -(-sin(cub->ray->angle) * *shortest_dist
				- (floor(cub->player->offset_y) + (cub->player->offset_y
						- floor(cub->player->offset_y)))) * cub->east->width[0];
	if (cub->ray->direction == SW)
		cub->ray->texture_offset_x = -(-sin(cub->ray->angle) * *shortest_dist
				- (floor(cub->player->offset_y) + (cub->player->offset_y
						- floor(cub->player->offset_y)))) * cub->west->width[0];
}

float	ft_dist_to_wall(t_cub *cub)
{
	float	shortest_dist;

	cub->ray->hit_wall = 0;
	shortest_dist = 0;
	while (!cub->ray->hit_wall)
	{
		cub->ray->dist_to_y = 999999;
		cub->ray->dist_to_x = 999999;
		if (cub->ray->angle != 0)
			cub->ray->dist_to_y = sqrtf(pow(cub->player->offset_y, 2)
					+ pow(cub->player->offset_y / tan(cub->ray->angle), 2));
		if (cub->ray->angle != M_PI * 0.5)
			cub->ray->dist_to_x = sqrtf(pow(cub->player->offset_x, 2)
					+ pow(cub->player->offset_x * tan(cub->ray->angle), 2));
		if (cub->ray->dist_to_y < cub->ray->dist_to_x)
			ft_nearest_wall_y(cub, &shortest_dist);
		else
			ft_nearest_wall_x(cub, &shortest_dist);
	}
	return (shortest_dist);
}
