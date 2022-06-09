/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:06:14 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/09 13:40:33 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_nearest_north_wall_y(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == NE)  // si angle NORD-EST
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->ray->dist_to_y;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_y++;
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->ray->dist_to_y;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_y++;
    }
}

void    ft_nearest_south_wall_y(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == SE)  // si angle SUD-EST
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->ray->dist_to_y;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_y++;
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->ray->dist_to_y;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_y++;
    }
}

void    ft_nearest_north_wall_x(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == NE)  // si angle NORD-EST
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->ray->dist_to_x;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_x++;
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->ray->dist_to_x;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_x++;
    }
}

void    ft_nearest_south_wall_x(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == SE)  // si angle SUD-EST
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->ray->dist_to_x;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_x++;
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->ray->dist_to_x;
            cub->ray->hit_wall = 1;
        }
        else
            cub->player->offset_x++;
    }
}
