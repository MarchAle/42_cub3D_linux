/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:34 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/06 17:37:49 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_nearest_wall_y(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= 3 * M_PI / 2 || angle <= M_PI / 2)   // si angle vers le NORD
    {

        ft_nearest_north_wall_y(cub, angle, shortest_dist);
    }
    else                                            // si angle vers le SUD
    {
        
        ft_nearest_south_wall_y(cub, angle, shortest_dist);
    }
}

void    ft_nearest_wall_x(t_cub *cub, float angle, float *shortest_dist)
{
    if (angle >= 3 * M_PI / 2 || angle <= M_PI / 2)   // si angle vers le NORD
        ft_nearest_north_wall_x(cub, angle, shortest_dist);
    else                                           // si angle vers le SUD
        ft_nearest_south_wall_x(cub, angle, shortest_dist);
}

float   ft_dist_to_wall(t_cub *cub, float angle)
{
    float   shortest_dist;

    shortest_dist = 0;
    cub->player->dist_to_y = 999999;
    cub->player->dist_to_x = 999999;
    if (cub->player->orientation != M_PI / 2 && cub->player->orientation != (3 * M_PI / 2))
        cub->player->dist_to_y = sqrtf(pow(cub->player->offset_y, 2) + pow(cub->player->offset_y / tan(angle), 2));
    if (cub->player->orientation != 0.0 && cub->player->orientation != M_PI)
        cub->player->dist_to_x = sqrtf(pow(cub->player->offset_x, 2) + pow(cub->player->offset_x * tan(angle), 2));
    // printf("dist_y : %f dist_x : %f\n", cub->player->dist_to_y, cub->player->dist_to_x);
    if (cub->player->dist_to_y < cub->player->dist_to_x)
    {
        ft_nearest_wall_y(cub, angle, &shortest_dist);
    }
    else
    {
        ft_nearest_wall_x(cub, angle, &shortest_dist);
    }
    return (shortest_dist);
}