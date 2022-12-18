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

void	ft_upper_screen(t_cub *cub, t_ray *ray, int i, int j, float dist)
{
	if (j > cub->calc->half_height - ray->wall_height * 0.5)
	{
		ft_render_wall(cub, ray, i, j, dist);
		(void)dist;
	}
	else
	{
		if (cub->mdata->sky == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->c_color);
		else
		{

			// pthread_mutex_lock(&cub->mutex);
			ft_render_sky(cub, ray, i, j);
			// pthread_mutex_unlock(&cub->mutex);
		}
	}
}

void	ft_lower_screen(t_cub *cub, t_ray *ray, int i, int j, float dist)
{
	if (j < cub->calc->half_height + ray->wall_height * 0.5)
	{

		ft_render_wall(cub, ray, i, j, dist);
		(void)dist;
	}
	else
	{
		if (cub->mdata->floor == NULL)
			my_mlx_pixel_put(cub->img, i, j, cub->mdata->f_color);
		else
		{
			// pthread_mutex_lock(&cub->mutex);
			ft_render_floor(cub, ray, i, j, dist);
			// pthread_mutex_unlock(&cub->mutex);

		}
	}
}

void	ft_render_img(t_cub *cub, t_ray *ray, int i)		//// print one column of pixel
{
	int	j = 0;
	float dist = ray->wall_dist;

	///// fisheye correction
	ray->wall_height = (HEIGHT_RATIO / (dist * cos(cub->player->orient - ray->angle))) * cub->mdata->screen[1];
	// pthread_mutex_lock(&cub->mutex);
	ray->sky_pixel_x = ((ray->angle) / cub->calc->piHalf) * cub->sky->width[0];
	// pthread_mutex_unlock(&cub->mutex);
	ft_sprites_calc(cub, ray);
	while (j < cub->mdata->screen[1] - 1)
	{
		// pthread_mutex_lock(&cub->mutex);
		if (j < cub->calc->half_height)
			ft_upper_screen(cub, ray, i, j, dist);
		else
			ft_lower_screen(cub, ray, i, j, dist);
		ft_render_sprites(cub, ray, i, j);
		// pthread_mutex_unlock(&cub->mutex);
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
	ft_lstfree_sprite(ray->sprites);
	ray->sprites = NULL;
	free(ray->sprites);
}

// void	ft_render_img2(t_cub *cub, t_ray *ray, int i)		//// print one column of pixel
// {
// 	int	j = 0;
// 	float dist = ray->wall_dist;

// 	///// fisheye correction
// 	ray->wall_height = (1 / (dist * cos(cub->player->orient - ray->angle))) * cub->mdata->screen[1];
// 	// pthread_mutex_lock(&cub->mutex);
// 	ray->sky_pixel_x = ((ray->angle) / cub->calc->piHalf) * cub->sky->width[0];
// 	// pthread_mutex_unlock(&cub->mutex);
// 	ft_sprites_calc(cub, ray);
// 	while (j < cub->mdata->screen[1] - 1)
// 	{
// 		// pthread_mutex_lock(&cub->mutex);
// 		if (j < cub->calc->half_height)
// 			ft_upper_screen(cub, ray, i, j, dist);
// 		else
// 			ft_lower_screen(cub, ray, i, j, dist);
// 		ft_render_sprites(cub, ray, i, j);
// 		// pthread_mutex_unlock(&cub->mutex);
// 		if (cub->blur == TRUE)
// 			j += 2;
// 		else
// 		{
// 			if (j < cub->mdata->screen[1] * 0.10 || j > cub->mdata->screen[1] * 0.90)
// 				j += 5;
// 			else if (j < cub->mdata->screen[1] * 0.15 || j > cub->mdata->screen[1] * 0.85)
// 				j += 4;
// 			else if (j < cub->mdata->screen[1] * 0.25 || j > cub->mdata->screen[1] * 0.70)
// 				j += 3;
// 			else if (j < cub->mdata->screen[1] * 0.40 || j > cub->mdata->screen[1] * 0.60)
// 				j += 2;
// 			else
// 				j++;
// 		}
// 	}
// 	(void)i;
// }
