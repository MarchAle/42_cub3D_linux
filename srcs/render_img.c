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

void	ft_upper_screen(t_cub *cub, int i, int j, float dist)
{
	if (j > cub->calc->half_height - cub->ray->wall_height * 0.5)
		ft_render_wall(cub, i, j, dist);
	else
	{
		if (cub->mdata->sky == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
		else
			ft_render_sky(cub, i, j);
	}
}

void	ft_lower_screen(t_cub *cub, int i, int j, float dist)
{
	if (j < cub->calc->half_height + cub->ray->wall_height * 0.5)
		ft_render_wall(cub, i, j, dist);
	else
	{
		if (cub->mdata->floor == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		else
			ft_render_floor(cub, i, j, dist);
	}
}

void	ft_render_img(t_cub *cub, float dist, int i)		//// print one column of pixel
{
	int	j = 0;

	///// fisheye correction
	cub->ray->wall_height = (1 / (dist * cos(cub->player->orient - cub->ray->angle))) * cub->mdata->screen[1];
	cub->sky_p->pixel_x = ((cub->ray->angle) / cub->calc->piHalf) * cub->sky->width[0];
	ft_sprites_calc(cub);
	while (j < cub->mdata->screen[1] - 1)
	{
		if (j < cub->calc->half_height)
			ft_upper_screen(cub, i, j, dist);
		else
			ft_lower_screen(cub, i, j, dist);
		ft_render_sprites(cub, i, j);
		if (cub->blur == TRUE)
			j += 2;
		else
		{
			if (j < cub->mdata->screen[1] * 0.10 || j > cub->mdata->screen[1] * 0.90)
				j += 5;
			else if (j < cub->mdata->screen[1] * 0.15 || j > cub->mdata->screen[1] * 0.85)
				j += 4;
			else if (j < cub->mdata->screen[1] * 0.25 || j > cub->mdata->screen[1] * 0.70)
				j += 3;
			else if (j < cub->mdata->screen[1] * 0.40 || j > cub->mdata->screen[1] * 0.60)
				j += 2;
			else
				j++;
		}
	}
}
