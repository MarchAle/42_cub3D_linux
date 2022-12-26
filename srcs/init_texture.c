/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:48:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:28:53 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_wall_texture(t_cub *cub)
{
	cub->north->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->no, cub->north->width, cub->north->height);
	cub->east->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->ea, cub->east->width, cub->east->height);
	cub->south->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->so, cub->south->width, cub->south->height);
	cub->west->img = mlx_xpm_file_to_image(cub->mlx->mlx,
			cub->mdata->we, cub->west->width, cub->west->height);
	cub->north->addr = mlx_get_data_addr(cub->north->img, &cub->north->bpp,
			&cub->north->line_length, &cub->north->endian);
	cub->east->addr = mlx_get_data_addr(cub->east->img, &cub->east->bpp,
			&cub->east->line_length, &cub->east->endian);
	cub->south->addr = mlx_get_data_addr(cub->south->img, &cub->south->bpp,
			&cub->south->line_length, &cub->south->endian);
	cub->west->addr = mlx_get_data_addr(cub->west->img, &cub->west->bpp,
			&cub->west->line_length, &cub->west->endian);
}

void	ft_init_texture(t_cub *cub)
{
	ft_init_wall_texture(cub);
	if (cub->mdata->sky)
	{
		cub->sky->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->sky, cub->sky->width, cub->sky->height);
		cub->sky->addr = mlx_get_data_addr(cub->sky->img, &cub->sky->bpp,
				&cub->sky->line_length, &cub->sky->endian);
	}
	if (cub->mdata->floor)
	{
		cub->floor->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->floor, cub->floor->width, cub->floor->height);
		cub->floor->addr = mlx_get_data_addr(cub->floor->img, &cub->floor->bpp,
				&cub->floor->line_length, &cub->floor->endian);
	}
	if (cub->mdata->sprite)
	{
		cub->sprite->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->sprite, cub->sprite->width, cub->sprite->height);
		cub->sprite->addr = mlx_get_data_addr(cub->sprite->img, &cub->sprite->bpp,
				&cub->sprite->line_length, &cub->sprite->endian);
	}
	if (cub->mdata->flashlight)
	{
		cub->flashlight->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->flashlight, cub->flashlight->width, cub->flashlight->height);
		cub->flashlight->addr = mlx_get_data_addr(cub->flashlight->img, &cub->flashlight->bpp,
				&cub->flashlight->line_length, &cub->flashlight->endian);
	}
	if (cub->mdata->door)
	{
		cub->door->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->door, cub->door->width, cub->door->height);
		cub->door->addr = mlx_get_data_addr(cub->door->img, &cub->door->bpp,
				&cub->door->line_length, &cub->door->endian);
	}
	if (cub->mdata->door_locked)
	{
		cub->door_locked->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->door_locked, cub->door_locked->width, cub->door_locked->height);
		cub->door_locked->addr = mlx_get_data_addr(cub->door_locked->img, &cub->door_locked->bpp,
				&cub->door_locked->line_length, &cub->door_locked->endian);
	}
	if (cub->mdata->key)
	{
		cub->key->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->key, cub->key->width, cub->key->height);
		cub->key->addr = mlx_get_data_addr(cub->key->img, &cub->key->bpp,
				&cub->key->line_length, &cub->key->endian);
	}
	if (cub->mdata->potion)
	{
		cub->potion->img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->mdata->potion, cub->potion->width, cub->potion->height);
		cub->potion->addr = mlx_get_data_addr(cub->potion->img, &cub->potion->bpp,
				&cub->potion->line_length, &cub->potion->endian);
	}
}
