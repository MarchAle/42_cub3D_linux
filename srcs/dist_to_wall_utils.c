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

void	ft_hit_wall(t_cub *cub, float *shortest_dist, int wall_orientation)
{
	cub->ray->hit_wall = 1;
	cub->ray->wall_orientation = wall_orientation;
	if (wall_orientation == N || wall_orientation == S)
		*shortest_dist = cub->ray->dist_to_y;
	else
		*shortest_dist = cub->ray->dist_to_x;
}

void	ft_nearest_north_wall_y(t_cub *cub, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1);
	if (cub->ray->direction == NE)
	{
		x = (int)floor(cub->player->x) + ((int)floor(cub->player->offset_x));
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, N);
		else
			cub->player->offset_y++;
	}
	else
	{
		x = (int)floor(cub->player->x) - ((int)floor(cub->player->offset_x));
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, N);
		else
			cub->player->offset_y++;
	}
}

void	ft_nearest_south_wall_y(t_cub *cub, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1);
	if (cub->ray->direction == SE)
	{
		x = (int)floor(cub->player->x) + ((int)floor(cub->player->offset_x));
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, S);
		else
			cub->player->offset_y++;
	}
	else
	{
		x = (int)floor(cub->player->x) - ((int)floor(cub->player->offset_x));
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, S);
		else
			cub->player->offset_y++;
	}
}

void	ft_nearest_north_wall_x(t_cub *cub, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y) - ((int)floor(cub->player->offset_y));
	if (cub->ray->direction == NE)
	{
		x = (int)floor(cub->player->x)
			+ ((int)floor(cub->player->offset_x) + 1);
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, E);
		else
			cub->player->offset_x++;
	}
	else
	{
		x = (int)floor(cub->player->x)
			- ((int)floor(cub->player->offset_x) + 1);
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, W);
		else
			cub->player->offset_x++;
	}
}

void	ft_nearest_south_wall_x(t_cub *cub, float *shortest_dist)
{
	int	x;
	int	y;

	y = (int)floor(cub->player->y)
		+ ((int)floor(cub->player->offset_y));
	if (cub->ray->direction == SE)
	{
		x = (int)floor(cub->player->x)
			+ ((int)floor(cub->player->offset_x) + 1);
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, E);
		else
			cub->player->offset_x++;
	}
	else
	{
		x = (int)floor(cub->player->x)
			- ((int)floor(cub->player->offset_x) + 1);
		if (cub->map[y][x] == '1')
			ft_hit_wall(cub, shortest_dist, W);
		else
			cub->player->offset_x++;
	}
}
