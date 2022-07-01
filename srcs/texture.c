/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:50:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/01 21:12:06 by amarchal         ###   ########.fr       */
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
	cub->sky->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->sky, cub->mlx->width, cub->mlx->height);
	cub->floor->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->floor, cub->mlx->width, cub->mlx->height);
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

int	ft_get_color_from_texture(char *addr, t_cub *cub)
{
	return (*(int*)(addr + ((int)cub->ray->texture_offset_y
			* cub->north->line_length + (int)cub->ray->texture_offset_x
			* (cub->north->bpp / 8))));
}

int	ft_get_color_from_texture_floor(char *addr, t_cub *cub, int x, int y)
{
	return (*(int*)(addr + (y * cub->north->line_length + x * (cub->north->bpp / 8))));
}

void	ft_shade_color(int *pix_color, float dist)
{
	int	r;
	int	g;
	int	b;

	if (dist > 2)
	{
		r = ((*pix_color & 0x00ff0000) >> 16) * (1 / (1 + (dist - 2)));
		g = ((*pix_color & 0x0000ff00) >> 8) * (1 / (1 + (dist - 2)));
		b = (*pix_color & 0x000000ff) * (1 / (1 + (dist - 2)));
		*pix_color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);	
	}
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
	ft_shade_color(&pix_color, dist);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
}

void	ft_print_floor(t_cub *cub, int i, int j, float dist)
{
	int		y_offset_px;
	float	y_offset;
	float	floor_angle;
	float	floor_dist;
	float	pixel_x;
	float	pixel_y;
	int		pix_color;

	y_offset_px = j - cub->mdata->screen[1] * 0.5;
	y_offset = y_offset_px / cub->ray->wall_height;
	floor_angle = y_offset / dist;
	floor_dist = ((cub->ray->wall_height * 0.5) / tan(floor_angle) / cub->ray->wall_height); // 
	ft_offset_init(cub);
	if (cub->ray->direction == SW)
	{
		pixel_x = cub->player->offset_x + (cos(cub->ray->angle) * floor_dist);
		pixel_y = cub->player->offset_y + (sin(cub->ray->angle) * floor_dist);
		
	}
	if (cub->ray->direction == NE)
	{
		pixel_x = cub->player->offset_x - (cos(cub->ray->angle) * floor_dist);
		pixel_y = cub->player->offset_y - (sin(cub->ray->angle) * floor_dist);
		
	}
	if (cub->ray->direction == SE)
	{
		pixel_x = cub->player->offset_x - (cos(cub->ray->angle) * floor_dist);
		pixel_y = cub->player->offset_y + (sin(cub->ray->angle) * floor_dist);
		
	}
	if (cub->ray->direction == NW)
	{
		pixel_x = cub->player->offset_x + (cos(cub->ray->angle) * floor_dist);
		pixel_y = cub->player->offset_y - (sin(cub->ray->angle) * floor_dist);
		
	}
	pixel_x = (floor(pixel_x) - pixel_x + 1) * TEX_WIDTH;
	pixel_y = (floor(pixel_y) - pixel_y + 1) * TEX_HEIGHT;
	if (cub->ray->direction == SW)
		pix_color = ft_get_color_from_texture_floor(cub->floor->addr, cub, TEX_HEIGHT - pixel_y, pixel_x);
	if (cub->ray->direction == NE)
		pix_color = ft_get_color_from_texture_floor(cub->floor->addr, cub, pixel_y, TEX_WIDTH - pixel_x);
	if (cub->ray->direction == SE)
		pix_color = ft_get_color_from_texture_floor(cub->floor->addr, cub, TEX_HEIGHT - pixel_y, TEX_WIDTH - pixel_x);
	if (cub->ray->direction == NW)
		pix_color = ft_get_color_from_texture_floor(cub->floor->addr, cub, pixel_y, pixel_x);
	ft_shade_color(&pix_color, floor_dist);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
}

void	ft_print_sky(t_cub *cub, int i, int j, float dist)
{
	int		y_offset_px;
	float	y_offset;
	float	floor_angle;
	float	floor_dist;
	float	pixel_x;
	float	pixel_y;
	int		pix_color;

	y_offset_px = (cub->mdata->screen[1] * 0.5) - j;
	y_offset = y_offset_px / cub->ray->wall_height;
	floor_angle = y_offset / dist;
	floor_dist = ((cub->ray->wall_height * 4.5) / tan(floor_angle) / cub->ray->wall_height);
	pixel_x = cub->player->x + (cos(cub->ray->angle) * floor_dist);
	pixel_y = cub->player->y - (sin(cub->ray->angle) * floor_dist);
	if (pixel_x < 0)
		pixel_x *= -1;
	while (pixel_x > 20)
		pixel_x -= 20;
	if (pixel_x < 0)
		pixel_x *= -1;
	pixel_x = pixel_x / 20 * TEX_WIDTH;
	if (pixel_y < 0)
		pixel_y *= -1;
	while (pixel_y > 20)
		pixel_y -= 20;
	if (pixel_y < 0)
		pixel_y *= -1;
	pixel_y = pixel_y / 20 * TEX_HEIGHT;
	pix_color = ft_get_color_from_texture_floor(cub->sky->addr, cub, pixel_y, pixel_x);
	// ft_shade_color(&pix_color, 3);
	my_mlx_pixel_put(cub->img, i, j, pix_color);
}

void	ft_draw_wall(t_cub *cub, float dist, int i)
{
	int	j;
	
	cub->ray->wall_height = (1 / (dist * cos(cub->ray->angle - cub->player->orient))) * cub->mdata->screen[1]; // fisheye
	j = 0;
	while (j < cub->mdata->screen[1])
	{
		if (j < cub->mdata->screen[1] * 0.5)
		{
			if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5)
				ft_print_texture(cub, i, j, dist);
			else
				ft_print_sky(cub, i, j, dist);
				// my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
		}
		else
		{
			if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5)
				ft_print_texture(cub, i, j, dist);
			else
				ft_print_floor(cub, i, j, dist);
				// my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		}
		j++;
	}
}
