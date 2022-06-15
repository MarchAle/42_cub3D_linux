/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:50:44 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/15 18:41:57 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_texture(t_cub *cub)
{
	cub->north->img = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone1.xpm", cub->north->x, cub->north->y);
	// cub->text->texture[0] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone1.xpm", cub->img->x, cub->img->y);
	// cub->text->texture[1] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone2.xpm", cub->img->x, cub->img->y);
	// cub->text->texture[2] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_stone3.xpm", cub->img->x, cub->img->y);
	// cub->text->texture[3] = mlx_xpm_file_to_image(cub->mlx->mlx, "../texture/wall_brick.xpm", cub->img->x, cub->img->y);
    cub->north->img = mlx_new_image(cub->mlx, TEX_WIDTH, TEX_HEIGHT);
    cub->north->addr = mlx_get_data_addr(cub->north->img, &cub->north->bits_per_pixel, &cub->north->line_length, &cub->north->endian);
    // cub->text->addr[0] = mlx_get_data_addr(cub->text->texture[0], &cub->text->bits_per_pixel[0], &cub->text->line_length[0], &cub->text->endian[0]);
    // cub->text->addr[1] = mlx_get_data_addr(cub->text->texture[1], &cub->text->bits_per_pixel[1], &cub->text->line_length[1], &cub->text->endian[1]);
    // cub->text->addr[2] = mlx_get_data_addr(cub->text->texture[2], &cub->text->bits_per_pixel[2], &cub->text->line_length[2], &cub->text->endian[2]);
    // cub->text->addr[3] = mlx_get_data_addr(cub->text->texture[3], &cub->text->bits_per_pixel[3], &cub->text->line_length[3], &cub->text->endian[3]);
    // printf("%s\n", cub->text->addr[0]);
}

void    ft_print_texture(t_cub *cub, int i, int j)
{
    int pix_color;
    
    // if (cub->ray->wall_height <= cub->mdata->screen[1])
    // {
        cub->ray->texture_offset_y = (float)j / (float)cub->mdata->screen[1] * TEX_HEIGHT; //  * (float)cub->ray->wall_height 
        if (cub->ray->wall_orientation == N)
        {
            // pix_color =  (int)(cub->north->addr + ((int)cub->ray->texture_offset_y * cub->north->line_length + (int)cub->ray->texture_offset_x * (cub->north->bits_per_pixel / 8)));
            pix_color = *(int*)(cub->north->addr + (4 * (int)cub->ray->texture_offset_y * TEX_WIDTH) + (4 * (int)cub->ray->texture_offset_x));
            // printf("offset_x %d | offset_y %d | j %d | wall_height %f\n", (int)cub->ray->texture_offset_x, (int)cub->ray->texture_offset_y, j, cub->ray->wall_height);
            my_mlx_pixel_put(cub->img, i, j, pix_color);
            // my_mlx_pixel_put(cub->img, i, j, 8553533);
        }
        else if (cub->ray->wall_orientation == S)
            my_mlx_pixel_put(cub->img, i, j, 8453533);
        else if (cub->ray->wall_orientation == E)
            my_mlx_pixel_put(cub->img, i, j, 8353533);
        else if (cub->ray->wall_orientation == W)
            my_mlx_pixel_put(cub->img, i, j, 8253533);
            
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