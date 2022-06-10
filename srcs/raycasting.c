/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:09:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/10 12:01:33 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void    ft_print_view(t_cub *cub)
{
    int     i;
    float   dist;
    t_img   *img;

	// if (cub->img)
    // 	mlx_destroy_image(cub->mlx, cub->img);
    img = malloc(sizeof(t_img));
    cub->img = img;
    cub->img->img = mlx_new_image(cub->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
    cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel, &cub->img->line_length, &cub->img->endian);
    i = 0;
    while (i < cub->mdata->screen[0])
    {
        dist = ft_raycast(i, cub) * (sin(cub->ray->angle) + cos(cub->ray->angle)); //  
        // if (cub->ray->wall_orientation == N || cub->ray->wall_orientation == S)
        //     dist *= sin(cub->ray->angle);
        ft_draw_wall(cub, dist, i);
        // i += 5;
        i++;
    }
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
}

void    ft_print_texture(t_cub *cub, int i, int j)
{
    if (cub->ray->wall_orientation == N)
        my_mlx_pixel_put(cub->img, i, j, 9653533);
    else if (cub->ray->wall_orientation == E)
        my_mlx_pixel_put(cub->img, i, j, 9553533);
    else if (cub->ray->wall_orientation == S)
        my_mlx_pixel_put(cub->img, i, j, 9453533);
    else if (cub->ray->wall_orientation == W)
        my_mlx_pixel_put(cub->img, i, j, 9353533);
}

    ///////////////// CALCUL HAUTEURS MURS /////////////////////////////
void    ft_draw_wall(t_cub *cub, float dist, int i)
{
    int j;

    cub->ray->wall_height = (1 / dist) * cub->mdata->screen[1];
    j = 0;
    while (j < cub->mdata->screen[1])
    {
        if (j < cub->mdata->screen[1] * 0.5)
        {
            if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5)
                ft_print_texture(cub, i ,j);
            else
                my_mlx_pixel_put(cub->img, i, j, 8653533);
        }
        else
        {
            if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5)
                ft_print_texture(cub, i ,j);
            else
                my_mlx_pixel_put(cub->img, i, j, 7653533);    
        }
        j++;
        // j += 5;
    }
}
////////////////////////////////////////////////////////////////////

float   ft_raycast(int i, t_cub *cub)
{
    float   dist;
    t_ray	*ray;
    
	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(EXIT_FAILURE);
    cub->ray = ray;
    cub->ray->angle = (cub->player->orientation + (-(30 * M_PI / 180) + ((60 * M_PI / 180) / cub->mdata->screen[0]) * i));
    cub->ray->mem_angle = cub->ray->angle;
	ft_get_direction(cub);
    ft_positive_angle(cub);
    
    ///////////// reinitialiser les offset
    cub->player->offset_x = cub->player->x - floor(cub->player->x);
    if (cub->ray->direction == NE || cub->ray->direction == SE)
        cub->player->offset_x = 1 - cub->player->offset_x;
    cub->player->offset_y = cub->player->y - floor(cub->player->y);
    if (cub->ray->direction == SW || cub->ray->direction == SE)
        cub->player->offset_y = 1 - cub->player->offset_y;
    /////////////
    
    dist = ft_dist_to_wall(cub);
    // if (cub->ray->dist_to_y < cub->ray->dist_to_x)
    //     printf("y ");
    // else
    //     printf("x ");
    // printf("%f\n", dist);
    ////////////// affiche rayons
    // float tmp_dist = 0;
    // while (tmp_dist < dist)
    // {
    //     cub->ray->x = cub->player->x + tmp_dist * cos(cub->ray->mem_angle);
    //     cub->ray->y = cub->player->y - tmp_dist * sin(cub->ray->mem_angle);
    //     my_mlx_pixel_put(cub->img, cub->ray->x * 100, cub->ray->y * 100, 0x00FF0000);
    //     tmp_dist += 0.01;
    // }
    
    // cub->ray->x = cub->player->x + dist * cos(cub->ray->mem_angle);
    // cub->ray->y = cub->player->y - dist * sin(cub->ray->mem_angle);
    // my_mlx_pixel_put(cub->img, cub->ray->x * 100, cub->ray->y * 100, 0x00FF0000);
    // printf(" x : %f | y : %f\n", cub->ray->x, cub->ray->y);
    /////////////
    return (dist);
}

void    ft_get_direction(t_cub *cub)
{
    if (cub->ray->angle >= M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= M_PI * 0.5 && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= M_PI * 0.5)
		cub->ray->direction = NE;
	else if (cub->ray->angle > - M_PI * 0.5 && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > - M_PI && cub->ray->angle <= - M_PI * 0.5)
		cub->ray->direction = SW;
}

void    ft_positive_angle(t_cub *cub) // Ramène angle à une valeur positive et comprise entre 0 (0deg) et PI * 0.5 (90deg)
{
	if (cub->ray->angle < 0)
		cub->ray->angle *= -1;
	while (cub->ray->angle > M_PI * 0.5)
        cub->ray->angle -= M_PI;
    if (cub->ray->angle < 0)
		cub->ray->angle *= -1;
}
