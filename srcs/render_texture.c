/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:50:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/02 19:39:25 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_texture(t_cub *cub)
{
	cub->north->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->NO, cub->north->width, cub->north->height);
	cub->east->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->EA, cub->east->width, cub->east->height);
	cub->south->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->SO, cub->south->width, cub->south->height);
	cub->west->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->WE, cub->west->width, cub->west->height);
	cub->sky->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->sky, cub->sky->width, cub->sky->height);
	cub->floor->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->floor, cub->floor->width, cub->floor->height);
	cub->north->addr = mlx_get_data_addr(cub->north->img, &cub->north->bpp,
			&cub->north->line_length, &cub->north->endian);
	cub->east->addr = mlx_get_data_addr(cub->east->img, &cub->east->bpp,
			&cub->east->line_length, &cub->east->endian);
	cub->south->addr = mlx_get_data_addr(cub->south->img, &cub->south->bpp,
			&cub->south->line_length, &cub->south->endian);
	cub->west->addr = mlx_get_data_addr(cub->west->img, &cub->west->bpp,
			&cub->west->line_length, &cub->west->endian);
	cub->sky->addr = mlx_get_data_addr(cub->sky->img, &cub->sky->bpp,
			&cub->sky->line_length, &cub->sky->endian);
	cub->floor->addr = mlx_get_data_addr(cub->floor->img, &cub->floor->bpp,
			&cub->floor->line_length, &cub->floor->endian);
}

int	ft_get_color_from_texture(t_texture *tex, int x, int y)
{
	return (*(int*)(tex->addr + (y * tex->line_length + x * (tex->bpp / 8))));
}

int	ft_shade_color(int pix_color, float dist)
{
	int	r;
	int	g;
	int	b;

	if (dist > 2)
	{
		r = ((pix_color & 0x00ff0000) >> 16) * (1 / (1 + (dist - 2)));
		g = ((pix_color & 0x0000ff00) >> 8) * (1 / (1 + (dist - 2)));
		b = (pix_color & 0x000000ff) * (1 / (1 + (dist - 2)));
		return((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);	
	}
	return (pix_color);
}

void	ft_draw_wall(t_cub *cub, float dist, int i)
{
	int	j;
	
	cub->ray->wall_height = (1 / (dist * cos(cub->ray->angle - cub->player->orient))) * cub->mdata->screen[1]; // fisheye
	j = 0;
	while (j < cub->mdata->screen[1] - 1)
	{
		if (j < cub->mdata->screen[1] * 0.5)
		{
			if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5)
			{
				
				ft_render_wall(cub, i, j, dist);
			}
			else if (i % 2 == 0)//  
			{
				// if (cub->mdata->sky != NULL)
				j = ft_render_sky(cub, i, j, dist);
				// else
				// 	my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
			}
		}
		else
		{
			if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5)
			{
				ft_render_wall(cub, i, j, dist);
				
			}
			else if (i % 2 == 0)//  
				j = ft_render_floor(cub, i, j, dist);
				// my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		}
		j++;
	}
}
