/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:34 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/09 15:37:18 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_nearest_wall_y(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == NW || cub->ray->direction == NE)   // si angle vers le NORD
        ft_nearest_north_wall_y(cub, shortest_dist);
    else                                                        // si angle vers le SUD
        ft_nearest_south_wall_y(cub, shortest_dist);
}

void    ft_nearest_wall_x(t_cub *cub, float *shortest_dist)
{
    if (cub->ray->direction == NW || cub->ray->direction == NE)   // si angle vers le NORD
        ft_nearest_north_wall_x(cub, shortest_dist);
    else                                                         // si angle vers le SUD
        ft_nearest_south_wall_x(cub, shortest_dist);
}

float   ft_dist_to_wall(t_cub *cub)
{
    float   shortest_dist;

    cub->ray->hit_wall = 0;
    shortest_dist = 0;
    while (!cub->ray->hit_wall)
    {
        cub->ray->dist_to_y = 999999;
        cub->ray->dist_to_x = 999999;
        if (cub->ray->angle != 0)
            cub->ray->dist_to_y = sqrtf(pow(cub->player->offset_y, 2) + pow(cub->player->offset_y / tan(cub->ray->angle), 2));
        if (cub->ray->angle != M_PI * 0.5)
            cub->ray->dist_to_x = sqrtf(pow(cub->player->offset_x, 2) + pow(cub->player->offset_x * tan(cub->ray->angle), 2));
        if (cub->ray->dist_to_y < cub->ray->dist_to_x)
            ft_nearest_wall_y(cub, &shortest_dist);
        else
            ft_nearest_wall_x(cub, &shortest_dist);
    }
    return (shortest_dist);
}