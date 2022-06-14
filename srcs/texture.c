/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:50:44 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/14 11:00:33 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_texture(t_cub *cub)
{
	cub->img->texture[0] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone1.xpm", cub->img->x, cub->img->y);
	cub->img->texture[1] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone2.xpm", cub->img->x, cub->img->y);
	cub->img->texture[2] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone3.xpm", cub->img->x, cub->img->y);
	cub->img->texture[3] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_brick.xpm", cub->img->x, cub->img->y);
}

void    ft_print_texture(t_cub *cub, int i, int j)
{
    if (cub->ray->wall_orientation == N)
        my_mlx_pixel_put(cub->img, i, j, 8753533);
    else if (cub->ray->wall_orientation == S)
        my_mlx_pixel_put(cub->img, i, j, 8453533);
    else if (cub->ray->wall_orientation == E)
        my_mlx_pixel_put(cub->img, i, j, 8353533);
    else if (cub->ray->wall_orientation == W)
        my_mlx_pixel_put(cub->img, i, j, 8253533);
}

void    ft_draw_wall(t_cub *cub, float dist, int i)
{
    int j;

    cub->ray->wall_height = (1 / dist) * cub->mdata->screen[1];
    j = 0;
    while (j < cub->mdata->screen[1])
    {
        if (j < cub->mdata->screen[1] * 0.5)
        {
            if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5) // mur cote ciel
                ft_print_texture(cub, i ,j);
            else
                my_mlx_pixel_put(cub->img, i, j, 8653533);
        }
        else
        {
            if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5) // mur cote sol
                ft_print_texture(cub, i ,j);
            else
                my_mlx_pixel_put(cub->img, i, j, 7653533);    
        }
        j++;
    }
}