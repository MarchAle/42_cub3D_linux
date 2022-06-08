/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:09:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/08 17:44:28 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_start_game(t_cub *cub)
{
    cub->player->orientation = M_PI / 2;     	// Look north
    // cub->player->orientation = 0.0;         		// Look east
    // cub->player->orientation = - M_PI / 2;     	// Look south
    // cub->player->orientation = M_PI;        		// Look west
    // cub->player->orientation = M_PI / 4;       	// Look North-East
    ft_mlx_init(cub);
    // ft_print_map(cub); // MINI-MAP
    ft_print_view(cub);
    // ft_print_img(cub);
	mlx_hook(cub->mlx->win, 17, 0, ft_exit, cub);
	mlx_hook(cub->mlx->win, 2, 0, key_hook, cub);
    mlx_loop(cub->mlx->mlx);
}

void    ft_print_view(t_cub *cub)
{
    int     i;
    // float   dist;

    i = 0;
    while (i < cub->mdata->screen[0])
    {
        ft_raycast(i, cub);
        i += 20;
    }
}

////////////// MERCREDI DRAW WALLS ////////////////////////////////
void    ft_draw_wall(t_cub *cub)
{
	int	x;
    int y;
    
	x = 0;
    y = ((cub->mdata->screen[1] / 2) - cub->ray->wall_height / 2);

    while (x < cub->mdata->screen[0])
    {
        // my_mlx_pixel_put(cub->mlx->mlx, x, y, 0x0000FF);
        x++;
	}
}
////////////////////////////////////////////////////////////////////

float   ft_raycast(int i, t_cub *cub)
{
    float   dist;
    t_ray	*ray;
    
    ///////////// reinitialiser les offset
    cub->player->offset_x = 0.5;
    cub->player->offset_y = 0.5;
    /////////////
	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(EXIT_FAILURE);
    cub->ray = ray;
    cub->ray->angle = (cub->player->orientation + (-(30 * M_PI / 180) + ((60 * M_PI / 180) / cub->mdata->screen[0]) * i));
	ft_get_direction(cub);
    ft_positive_angle(cub);
    dist = ft_dist_to_wall(cub);
    printf("dist wall = %f\n", dist);

    ///////////////// MERCREDI // CALCUL HAUTEURS MURS /////////////////////////////
    if (dist == 0) // si mur juste a cote hauteur calculee par rapport a x
    {
        // sidedistx = distance jusque premiere intersection x
        // delta dist x = distance entre deux intersection de x
        // sidedist y = dist jusque premiere inter y
        // deltadist y = dist entre deux intersections y
        // hauteur mur = sidedistx - deltadistx // pareil avec y
        cub->ray->wall_height = cub->ray->dist_to_x - cub->player->offset_x;
        ft_draw_wall(cub);
        printf("wall_height x = %f\n", cub->ray->wall_height);
    }
    else // si mur est loin hauteur calculee p/r a y
    {
        cub->ray->wall_height = cub->ray->dist_to_y - cub->player->offset_y;
        ft_draw_wall(cub);
        printf("wall_height y = %f\n", cub->ray->wall_height);
    }
    ///////////////////////////////////////////////////////////////////////////////
    
    if (cub->ray->dist_to_y < cub->ray->dist_to_x)
        printf("y ");
    else
        printf("x ");
    printf("%f\n", dist);
    return (dist);
}

void    ft_get_direction(t_cub *cub)
{
    if (cub->ray->angle >= M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= M_PI / 2 && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= M_PI / 2)
		cub->ray->direction = NE;
	else if (cub->ray->angle > - M_PI / 2 && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > - M_PI && cub->ray->angle <= - M_PI / 2)
		cub->ray->direction = SW;
}

void    ft_positive_angle(t_cub *cub) // Ramène angle à une valeur positive et comprise entre 0 (0deg) et PI / 2 (90deg)
{
	if (cub->ray->angle < 0)
		cub->ray->angle *= -1;
	while (cub->ray->angle > M_PI / 2)
        cub->ray->angle -= M_PI;
    if (cub->ray->angle < 0)
		cub->ray->angle *= -1;
}
