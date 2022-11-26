/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:01:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 15:57:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static	void ft_param_calc(t_cub *cub, int j)
{
	// cub->sky_p->pixel_x = ((cub->ray->angle) / (2 * M_PI)) * cub->sky->width[0];
	cub->sky_p->pixel_y = cub->sky->height[0] - (((cub->mdata->screen[1]
					* 0.75 - j) / (cub->mdata->screen[1] * 0.75))
			* cub->sky->height[0] - 50);
}

void	ft_render_sky(t_cub *cub, int i, int j)
{
	int		pix_color;

	ft_param_calc(cub, j);
	pix_color = ft_get_color_from_texture(cub->sky,
			(int)cub->sky_p->pixel_x, (int)cub->sky_p->pixel_y);
	// my_mlx_pixel_put(cub->img, i, j, pix_color);
	ft_multi_pixel_put(cub, cub->img, i, j, ft_downscaling(cub, i, j), pix_color);
}
