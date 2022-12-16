/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:06:14 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:45:20 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_hit_wall(t_ray *ray, float *shortest_dist, int wall_orientation)
{
	ray->hit_wall = 1;
	ray->wall_orientation = wall_orientation;
	if (wall_orientation == N || wall_orientation == S)
		*shortest_dist = ray->dist_to_y;
	else
		*shortest_dist = ray->dist_to_x;
}

void	ft_nearest_north_wall_y(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1);
	if (ray->direction == NE)
	{
		x = (int)floor(cub->player->x) + ((int)floor(cub->player->offset_x));
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_y + 0.5 / ray->sinAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, Y, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, N);
		else
			cub->player->offset_y++;
	}
	else
	{
		x = (int)floor(cub->player->x) - ((int)floor(cub->player->offset_x));
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_y + 0.5 / ray->sinAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, Y, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, N);
		else
			cub->player->offset_y++;
	}
}

void	ft_nearest_south_wall_y(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1);
	if (ray->direction == SE)
	{
		x = (int)floor(cub->player->x) + ((int)floor(cub->player->offset_x));
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_y - 0.5 / ray->sinAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, Y, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, S);
		else
			cub->player->offset_y++;
	}
	else
	{
		x = (int)floor(cub->player->x) - ((int)floor(cub->player->offset_x));
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_y - 0.5 / ray->sinAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, Y, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, S);
		else
			cub->player->offset_y++;
	}
}

void	ft_nearest_north_wall_x(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) - ((int)floor(cub->player->offset_y));
	if (ray->direction == NE)
	{
		x = (int)floor(cub->player->x)
			+ ((int)floor(cub->player->offset_x) + 1);
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_x + 0.5 / ray->cosAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, X, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, E);
		else
			cub->player->offset_x++;
	}
	else
	{
		x = (int)floor(cub->player->x)
			- ((int)floor(cub->player->offset_x) + 1);
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_x - 0.5 / ray->cosAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, X, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, W);
		else
			cub->player->offset_x++;
	}
}

void	ft_nearest_south_wall_x(t_cub *cub, t_ray *ray, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y)
		+ ((int)floor(cub->player->offset_y));
	if (ray->direction == SE)
	{
		x = (int)floor(cub->player->x)
			+ ((int)floor(cub->player->offset_x) + 1);
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_x + 0.5 / ray->cosAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, X, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, E);
		else
			cub->player->offset_x++;
	}
	else
	{
		x = (int)floor(cub->player->x)
			- ((int)floor(cub->player->offset_x) + 1);
		if (cub->monster_map[y][x] == 'x' && (cub->map[y][x] == '0' || cub->map[y][x] == 'X')) // monster hit
		{
			monster_detected(cub, ray, x, y);
			// ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x + 0.5, y + 0.5, MONSTER, 0, 0));
		}
		if (cub->map[y][x] == 'D') // door hit
		{
			float corrected_dist = ray->dist_to_x - 0.5 / ray->cosAngle;
			ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(x, y, DOOR, corrected_dist, x_offset_calc(cub, ray, corrected_dist, X, DOOR)));
		}
		if (cub->map[y][x] == '1')
			ft_hit_wall(ray, shortest_dist, W);
		else
			cub->player->offset_x++;
	}
}
