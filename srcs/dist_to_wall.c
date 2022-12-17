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

float	x_offset_calc(t_cub *cub, t_ray *ray, float dist, int axe, int type)
{
	if (type == DOOR)
	{
		if (axe == Y)
		{
			if (ray->direction == NE)
				return (((ray->cosAngle * dist) - (ray->offset_x - 1)));
			else if (ray->direction == SE)
				return (((ray->cosAngle * dist) - (ray->offset_x - 1)));
			else if (ray->direction == NW)
				return (-(-ray->cosAngle * dist - (floor(ray->offset_x) + (ray->offset_x - floor(ray->offset_x)))));
			else if (ray->direction == SW)
				return (-(-ray->cosAngle * dist - (floor(ray->offset_x) + (ray->offset_x - floor(ray->offset_x)))));
		}
		else if (axe == X)
		{
			if (ray->direction == NE)
				return (((ray->sinAngle * dist)	- (ray->offset_y - 1)));
			else if (ray->direction == NW)
				return (((ray->sinAngle * dist)	- (ray->offset_y - 1)));
			else if (ray->direction == SE)
				return (-(-ray->sinAngle * dist	- (floor(ray->offset_y) + (ray->offset_y - floor(ray->offset_y)))));
			else if (ray->direction == SW)
				return (-(-ray->sinAngle * dist	- (floor(ray->offset_y) + (ray->offset_y - floor(ray->offset_y)))));
			
		}
	}
	if (axe == Y)
	{
		if (ray->direction == NE)
			ray->texture_offset_x = ((ray->cosAngle * dist)	- (ray->offset_x - 1)) * cub->north->width[0];
		else if (ray->direction == SE)
			ray->texture_offset_x = ((ray->cosAngle * dist)	- (ray->offset_x - 1)) * cub->south->width[0];
		else if (ray->direction == NW)
			ray->texture_offset_x = -(-ray->cosAngle * dist	- (floor(ray->offset_x) + (ray->offset_x - floor(ray->offset_x)))) * cub->north->width[0];
		else if (ray->direction == SW)
			ray->texture_offset_x = -(-ray->cosAngle * dist	- (floor(ray->offset_x) + (ray->offset_x - floor(ray->offset_x)))) * cub->south->width[0];
	}
	else if (axe == X)
	{
		if (ray->direction == NE)
			ray->texture_offset_x = ((ray->sinAngle * dist)	- (ray->offset_y - 1)) * cub->east->width[0];
		else if (ray->direction == NW)
			ray->texture_offset_x = ((ray->sinAngle * dist)	- (ray->offset_y - 1)) * cub->west->width[0];
		else if (ray->direction == SE)
			ray->texture_offset_x = -(-ray->sinAngle * dist	- (floor(ray->offset_y) + (ray->offset_y - floor(ray->offset_y)))) * cub->east->width[0];
		else if (ray->direction == SW)
			ray->texture_offset_x = -(-ray->sinAngle * dist	- (floor(ray->offset_y) + (ray->offset_y - floor(ray->offset_y)))) * cub->west->width[0];
	}
	// printf("wall offset %f\n", ray->texture_offset_x);

	return (0);
}

void	ft_nearest_wall_y(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	if (ray->direction == NW || ray->direction == NE)
		ft_nearest_north_wall_y(cub, ray, shortest_dist);
	else
		ft_nearest_south_wall_y(cub, ray, shortest_dist);
	if (ray->hit_wall)
		x_offset_calc(cub, ray, *shortest_dist, Y, WALL);
}

void	ft_nearest_wall_x(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	if (ray->direction == NW || ray->direction == NE)
		ft_nearest_north_wall_x(cub, ray, shortest_dist);
	else
		ft_nearest_south_wall_x(cub, ray, shortest_dist);
	if (ray->hit_wall)
		x_offset_calc(cub, ray, *shortest_dist, X, WALL);
}

float	ft_dist_to_wall(t_cub *cub, t_ray *ray)
{
	float	shortest_dist;

	ray->hit_wall = 0;
	shortest_dist = 0;
	while (!ray->hit_wall)
	{
		ray->dist_to_y = 999999;
		ray->dist_to_x = 999999;
		if (ray->angle != 0)
			ray->dist_to_y = sqrtf(pow(ray->offset_y, 2)
					+ pow(ray->offset_y / ray->tanAngle, 2));
		if (ray->angle != cub->calc->piHalf)
			ray->dist_to_x = sqrtf(pow(ray->offset_x, 2)
					+ pow(ray->offset_x * ray->tanAngle, 2));
		if (ray->dist_to_y < ray->dist_to_x)
			ft_nearest_wall_y(cub, ray, &shortest_dist);
		else
			ft_nearest_wall_x(cub, ray, &shortest_dist);
	}
	return (shortest_dist);
}
