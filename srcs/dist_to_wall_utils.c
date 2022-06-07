/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:06:14 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/06 17:33:37 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_nearest_north_wall_y(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= 0 && angle <= M_PI / 2)  // si angle NORD-EST
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->player->dist_to_y;
        }
        else
        {
            cub->player->offset_y++;
            ft_dist_to_wall(cub, angle);
        }
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->player->dist_to_y;
        }
        else
        {
            cub->player->offset_y++;
            ft_dist_to_wall(cub, angle);
        }
    }
}

void    ft_nearest_south_wall_y(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= M_PI / 2 && angle <= M_PI)  // si angle SUD-EST
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->player->dist_to_y;
        }
        else
        {
            cub->player->offset_y++;
            ft_dist_to_wall(cub, angle);
        }
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y) + 1)][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x))] == '1')
        {
            *shortest_dist = cub->player->dist_to_y;
        }
        else
        {
            cub->player->offset_y++;
            ft_dist_to_wall(cub, angle);
        }
    }
}

void    ft_nearest_north_wall_x(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= 0 && angle <= M_PI / 2)  // si angle NORD-EST
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->player->dist_to_x;
        }
        else
        {
            cub->player->offset_x++;
            ft_dist_to_wall(cub, angle);
        }
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) - ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->player->dist_to_x;
        }
        else
        {
            cub->player->offset_x++;
            ft_dist_to_wall(cub, angle);
        }
    }
}

void    ft_nearest_south_wall_x(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= M_PI / 2 && angle <= M_PI)  // si angle SUD-EST
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) + ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->player->dist_to_x;
        }
        else
        {
            cub->player->offset_x++;
            ft_dist_to_wall(cub, angle);
        }
    }
    else
    {
        if (cub->map[(int)floor(cub->player->y) + ((int)floor(cub->player->offset_y))][(int)floor(cub->player->x) - ((int)floor(cub->player->offset_x) + 1)] == '1')
        {
            *shortest_dist = cub->player->dist_to_x;
        }
        else
        {
            cub->player->offset_x++;
            ft_dist_to_wall(cub, angle);
        }
    }
}
