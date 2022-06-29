/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:50:44 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/29 14:41:26 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_texture(t_cub *cub)
{
	cub->north->img = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_brick.xpm", cub->mlx->width, cub->mlx->height);
	// cub->east->img = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_stone1.xpm", cub->mlx->width, cub->mlx->height);
    printf("OUI\n");
	// cub->south->img = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_stone2.xpm", cub->mlx->width, cub->mlx->height);
	// cub->west->img = mlx_xpm_file_to_image(cub->mlx->mlx, "./texture/wall_stone3.xpm", cub->mlx->width, cub->mlx->height);
	// cub->text->img = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_brick.xpm", cub->img->x, cub->img->y);
    // cub->north->img = mlx_new_image(cub->mlx, TEX_WIDTH, TEX_HEIGHT);
    cub->north->addr = mlx_get_data_addr(cub->north->img, &cub->north->bits_per_pixel, &cub->north->line_length, &cub->north->endian);
    // cub->east->addr = mlx_get_data_addr(cub->east->img, &cub->east->bits_per_pixel, &cub->east->line_length, &cub->east->endian);
    // cub->south->addr = mlx_get_data_addr(cub->south->img, &cub->south->bits_per_pixel, &cub->south->line_length, &cub->south->endian);
    // cub->west->addr = mlx_get_data_addr(cub->west->img, &cub->west->bits_per_pixel, &cub->west->line_length, &cub->west->endian);
    // cub->text->addr[3] = mlx_get_data_addr(cub->text->texture[3], &cub->text->bits_per_pixel[3], &cub->text->line_length[3], &cub->text->endian[3]);
    // printf("%s\n", cub->text->addr[0]);
}

void    ft_print_texture(t_cub *cub, int i, int j)
{
    int pix_color = 8153533;
    // void    *test;

    // if (cub->ray->wall_height <= cub->mdata->screen[1])
    // {
        cub->ray->texture_offset_y = ((float)j - (((float)cub->mdata->screen[1] - (float)cub->ray->wall_height) / 2)) / ((float)cub->ray->wall_height) * TEX_HEIGHT;
        if (cub->ray->wall_orientation == N)
        {
            pix_color = *(int*)(cub->north->addr + ((int)cub->ray->texture_offset_y * cub->north->line_length + (int)cub->ray->texture_offset_x * (cub->north->bits_per_pixel / 8)));
            my_mlx_pixel_put(cub->img, i, j, pix_color);
        }
        else if (cub->ray->wall_orientation == S)
        {
            // pix_color = *(int*)(cub->south->addr + ((int)cub->ray->texture_offset_y * cub->north->line_length + (int)cub->ray->texture_offset_x * (cub->north->bits_per_pixel / 8)));
            
            my_mlx_pixel_put(cub->img, i, j, 8453533);
        }
        else if (cub->ray->wall_orientation == E)
        {
            // pix_color = *(int*)(cub->east->addr + ((int)cub->ray->texture_offset_y * cub->north->line_length + (int)cub->ray->texture_offset_x * (cub->north->bits_per_pixel / 8)));
            
            my_mlx_pixel_put(cub->img, i, j, 8353533);
        }
        else if (cub->ray->wall_orientation == W)
        {
            // pix_color = *(int*)(cub->west->addr + ((int)cub->ray->texture_offset_y * cub->north->line_length + (int)cub->ray->texture_offset_x * (cub->north->bits_per_pixel / 8)));
            
            my_mlx_pixel_put(cub->img, i, j, 8253533);
        }
            
        // my_mlx_pixel_put(cub->img, i, j, pix_color);
    // }
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