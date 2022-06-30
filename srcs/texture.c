/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:50:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/30 19:08:57 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_texture(t_cub *cub)
{
	cub->north->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->NO, cub->north->x, cub->north->y);
	cub->east->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->EA, cub->east->x, cub->east->y);
	cub->south->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->SO, cub->mlx->width, cub->mlx->height);
	cub->west->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->WE, cub->mlx->width, cub->mlx->height);
	cub->north->addr = mlx_get_data_addr(cub->north->img, &cub->north->bpp,
			&cub->north->line_length, &cub->north->endian);
	cub->east->addr = mlx_get_data_addr(cub->east->img, &cub->east->bpp,
			&cub->east->line_length, &cub->east->endian);
	cub->south->addr = mlx_get_data_addr(cub->south->img, &cub->south->bpp,
			&cub->south->line_length, &cub->south->endian);
	cub->west->addr = mlx_get_data_addr(cub->west->img, &cub->west->bpp,
			&cub->west->line_length, &cub->west->endian);
}

int	ft_get_color_from_texture(char *addr, t_cub *cub)
{
	return (*(int*)(addr + ((int)cub->ray->texture_offset_y
			* cub->north->line_length + (int)cub->ray->texture_offset_x
			* (cub->north->bpp / 8))));
}

void	ft_shade_color(int *pix_color, float dist)
{
	*pix_color -= (int)(dist * 50);
}

void	ft_print_texture(t_cub *cub, int i, int j, float dist)
{
	int	pix_color;

	pix_color = 0;
	cub->ray->texture_offset_y = (float)((j - ((cub->mdata->screen[1]
		- cub->ray->wall_height) / 2)) / (cub->ray->wall_height)
		* TEX_HEIGHT);
	if (cub->ray->wall_orientation == N)
		pix_color = ft_get_color_from_texture(cub->north->addr, cub);
	else if (cub->ray->wall_orientation == S)
		pix_color = ft_get_color_from_texture(cub->south->addr, cub);
	else if (cub->ray->wall_orientation == E)
		pix_color = ft_get_color_from_texture(cub->east->addr, cub);
	else if (cub->ray->wall_orientation == W)
		pix_color = ft_get_color_from_texture(cub->west->addr, cub);
	// ft_shade_color(&pix_color, dist);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
	(void)dist;
}

void	ft_draw_wall(t_cub *cub, float dist, int i)
{
	int	j;

	cub->ray->wall_height = (1 / dist) * cub->mdata->screen[1];
	j = 0;
	while (j < cub->mdata->screen[1])
	{
		if (j < cub->mdata->screen[1] * 0.5)
		{
			if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5)
				ft_print_texture(cub, i, j, dist);
			else
				my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
		}
		else
		{
			if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5)
				ft_print_texture(cub, i, j, dist);
			else
				my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		}
		j++;
	}
}
