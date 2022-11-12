/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:50:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:37:47 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_upper_screen(t_cub *cub, int i, int j, float dist)
{
	if (j > cub->mdata->screen[1] * 0.5 - cub->ray->wall_height * 0.5)
		ft_render_wall(cub, i, j, dist);
	else
	{
		if (cub->mdata->sky == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
		else
			j = ft_render_sky(cub, i, j);
	}
	ft_render_sprites(cub, i, j);
	return (j);
}

int	ft_lower_screen(t_cub *cub, int i, int j, float dist)
{
	int sprite_j = j;
	if (j < cub->mdata->screen[1] * 0.5 + cub->ray->wall_height * 0.5)
		ft_render_wall(cub, i, j, dist);
	else
	{
		if (cub->mdata->floor == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		else if (i % 2 == 0)
			j = ft_render_floor(cub, i, j, dist);
	}
	ft_render_sprites(cub, i, sprite_j);
	return (j);
}

void	ft_render_img(t_cub *cub, float dist, int i)
{
	int	j;

	///// fisheye correction
	cub->ray->wall_height = (1 / (dist * cos(cub->player->orient - cub->ray->angle))) * cub->mdata->screen[1];
	j = 0;
	ft_sprites_calc(cub);
	while (j < cub->mdata->screen[1] - 1)
	{
		if (j < cub->mdata->screen[1] * 0.5)
			j = ft_upper_screen(cub, i, j, dist);
		else
			j = ft_lower_screen(cub, i, j, dist);
		//ft_render_sprites(cub, i, j);
		if (cub->blur == TRUE)
			j += 2;
		else
			j++;
	}
}
