/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:09:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/29 11:20:39 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_print_view(t_cub *cub)
{
    int     i;
    float   dist;
    t_img   *img;

    img = malloc(sizeof(t_img));
    cub->img = img;
    cub->img->img = mlx_new_image(cub->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
    cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel, &cub->img->line_length, &cub->img->endian);
    i = cub->mdata->screen[0];
    while (i > 0)
    {
        dist = ft_raycast(i, cub, FALSE) * cos(cub->ray->angle - cub->player->orientation);
        ft_draw_wall(cub, dist, cub->mdata->screen[0] - i);
        i--;
    }
    if (cub->minimap == TRUE)
        ft_mini_map(cub);

    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	// void	*test;
	// test = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_brick.xpm", cub->mlx->width, cub->mlx->height);
	// cub->north = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_brick.xpm", cub->mlx->width, cub->mlx->height);
    // mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, test, 248, 248);
    // mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->north, 248, 248);
    
    mlx_destroy_image(cub->mlx->mlx, cub->img->img);
}

void    ft_offset_init(t_cub *cub)
{
    cub->player->offset_x = cub->player->x - floor(cub->player->x);
    if (cub->ray->direction == NE || cub->ray->direction == SE)
        cub->player->offset_x = 1 - cub->player->offset_x;
    cub->player->offset_y = cub->player->y - floor(cub->player->y);
    if (cub->ray->direction == SW || cub->ray->direction == SE)
        cub->player->offset_y = 1 - cub->player->offset_y;
}

float   ft_raycast(int i, t_cub *cub, int print_ray)
{
    float   dist;
    float tmp_dist;
    
    tmp_dist = 0;
    cub->ray->angle = (cub->player->orientation + (-(30 * M_PI / 180) + ((60 * M_PI / 180) / cub->mdata->screen[0]) * i));
    ft_get_direction(cub);
    ft_offset_init(cub);
    dist = ft_dist_to_wall(cub);
    if (print_ray == TRUE)
    {
        while (tmp_dist < dist)
        {
            cub->ray->x = cub->player->x + tmp_dist * cos(cub->ray->angle);
            cub->ray->y = cub->player->y - tmp_dist * sin(cub->ray->angle);
            my_mlx_pixel_put(cub->img, cub->ray->x * 25 + 50, cub->ray->y * 25 + 30, 0x86f6ff73);
            tmp_dist += 0.01;
        }
        cub->ray->x = cub->player->x + dist * cos(cub->ray->angle);
        cub->ray->y = cub->player->y - dist * sin(cub->ray->angle);
        my_mlx_pixel_put(cub->img, cub->ray->x * 25 + 50, cub->ray->y * 25 + 30, 0x86f6ff73);
    }
    return (dist);
}

void    ft_get_direction(t_cub *cub)
{
    if (cub->ray->angle <= - M_PI * 0.5 && cub->ray->angle >= - M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= M_PI * 0.5 && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= M_PI * 0.5)
		cub->ray->direction = NE;
	else if (cub->ray->angle > - M_PI * 0.5 && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > - M_PI && cub->ray->angle <= - M_PI * 0.5)
		cub->ray->direction = SW;
	else if (cub->ray->angle > M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle < - M_PI)
		cub->ray->direction = NW;
}
