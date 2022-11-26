/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:02:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 11:01:09 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		avgColorCalc(t_cub *cub, int x, int y, int blurIntensity)
{
	int avgred = 0;
	int avggreen = 0;
	int avgblue = 0;
	int i = x - blurIntensity;
	int div = 1;

	while (i < x + blurIntensity)
	{
		int j = y - blurIntensity;
		while (j < y + blurIntensity)
		{
			if ((i > 0 && i < cub->mdata->screen[0]) && (j > 0 && j < cub->mdata->screen[1]))
			{
				avgred += (ft_get_color_from_img(cub->img, i, j) & 0x00ff0000) >> 16;
				avggreen += (ft_get_color_from_img(cub->img, i, j) & 0x0000ff00) >> 8;
				avgblue += (ft_get_color_from_img(cub->img, i, j) & 0x000000ff);
				div++;
			}
			j += 2;
		}
		i += 2;
	}
	return ((((avgred / div) & 0xff) << 16) + (((avggreen / div) & 0xff) << 8) + ((avgblue / div) & 0xff));
}


void	ft_blur(t_cub *cub, int blurIntensity) //
{
	t_img	*blur_img;
	int i = 1;
	int j;
	int avgColor = 0;
	int downscaling = 4;

	blur_img = malloc(sizeof(t_img));
	if (!blur_img)
		ft_error(MALLOC);
	blur_img->img = mlx_new_image(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
	blur_img->addr = mlx_get_data_addr(blur_img->img, &blur_img->bits_per_pixel, &blur_img->line_length, &cub->img->endian);

	while (i < cub->mdata->screen[0])
	{
		j = 1;
		while (j < cub->mdata->screen[1])
		{
			avgColor = avgColorCalc(cub, i, j, blurIntensity);
			ft_multi_pixel_put(cub, blur_img, i, j, downscaling, avgColor);
			j += downscaling;
		}
		i += downscaling;
	}
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, blur_img->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, blur_img->img);
}

void	ft_print_view(t_cub *cub)
{
	int		i;
	float	dist;
	t_img	*img;


	img = malloc(sizeof(t_img));
	if (!img)
		ft_error(MALLOC);
	cub->img = img;
	cub->img->img = mlx_new_image(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel, &cub->img->line_length, &cub->img->endian);
	i = cub->mdata->screen[0];
	while (i > 0)
	{
		dist = ft_raycast(i, cub, FALSE, 0);
		ft_render_img(cub, dist, cub->mdata->screen[0] - i);
		ft_lstfree(&cub->ray->sprites);
		if (cub->blur == TRUE)
			i -= 2;
		else
		{
			if (i < cub->mdata->screen[0] * 0.10 || i > cub->mdata->screen[0] * 0.90)
				i -= 5;
			else if (i < cub->mdata->screen[0] * 0.15 || i > cub->mdata->screen[0] * 0.85)
				i -= 4;
			else if (i < cub->mdata->screen[0] * 0.25 || i > cub->mdata->screen[0] * 0.75)
				i -= 3;
			else if (i < cub->mdata->screen[0] * 0.40 || i > cub->mdata->screen[0] * 0.60)
				i -= 2;
			else
				i--;
		}
	}
	if (cub->minimap == TRUE)
		ft_mini_map(cub);
	if (cub->blur == TRUE)
	{
		// pthread_t 	thread = 0;
		// pthread_create(&thread, NULL, ft_blur, &cub);
		// pthread_join(thread, NULL);
		ft_blur(cub, 7);
	}
	else
		mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->flashlight->img, cub->mdata->screen[0] - cub->flashlight->width[0], cub->mdata->screen[1] - cub->flashlight->height[0]);
	mlx_destroy_image(cub->mlx->mlx, cub->img->img);
	free(img);
	cub->frames++;
}

void	ft_offset_init(t_cub *cub)
{
	cub->player->offset_x = cub->player->x - floor(cub->player->x);
	if (cub->ray->direction == NE || cub->ray->direction == SE)
		cub->player->offset_x = 1 - cub->player->offset_x;
	cub->player->offset_y = cub->player->y - floor(cub->player->y);
	if (cub->ray->direction == SW || cub->ray->direction == SE)
		cub->player->offset_y = 1 - cub->player->offset_y;
}

float	ft_angleCalculation(int i, t_cub *cub)
{
	float a = sqrtf(pow(i, 2) + cub->calc->powd - (2 * i * cub->calc->d * cub->calc->cosalpha));
	float angle = asin(cub->calc->sinalpha * i / a);
	cub->ray->angle_player = cub->calc->fovHalf - angle;
	return (angle);
}

float	ft_raycast(int i, t_cub *cub, int print_ray, int minimap_size)
{
	float	dist;
	float	tmp_dist;
	int		ray_color;

	tmp_dist = 0;
	cub->ray->angle = cub->player->orient - cub->calc->fovHalf + ft_angleCalculation(i, cub);
	ft_trigo_angle(cub);
	ft_get_direction(cub);
	ft_offset_init(cub);
	dist = ft_dist_to_wall(cub);
	if (print_ray == TRUE)
	{
		while (tmp_dist < dist && tmp_dist < 8)
		{
			ray_color = 0x0D062B;
			cub->ray->x = cub->player->x + tmp_dist * cub->calc->cosAngle;
			cub->ray->y = cub->player->y - tmp_dist * cub->calc->sinAngle;
			ray_color = ft_fade_color(ray_color, tmp_dist);
			my_mlx_pixel_put(cub->img, cub->ray->x * minimap_size + 30,
				cub->ray->y * minimap_size + 80, ray_color);
			tmp_dist += 0.08;
		}
	}
	return (dist);
}

void	ft_get_direction(t_cub *cub)
{
	if (cub->ray->angle <= -cub->calc->piHalf && cub->ray->angle >= -M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= cub->calc->piHalf && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= cub->calc->piHalf)
		cub->ray->direction = NE;
	else if (cub->ray->angle > -cub->calc->piHalf && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > -M_PI && cub->ray->angle <= -cub->calc->piHalf)
		cub->ray->direction = SW;
	else if (cub->ray->angle > M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle < -M_PI)
		cub->ray->direction = NW;
}
