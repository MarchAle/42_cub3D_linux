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

void	ft_print_view(t_cub *cub)
{
	int		i;
	float	dist;
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		ft_error(MALLOC);
	cub->img = img;
	cub->img->img = mlx_new_image(cub->mlx,
			cub->mdata->screen[0], cub->mdata->screen[1]);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	i = cub->mdata->screen[0];
	while (i > 0)
	{
		dist = ft_raycast(i, cub, FALSE, 0);
		ft_render_img(cub, dist, cub->mdata->screen[0] - i);
		i--;
	}
	if (cub->minimap == TRUE)
		ft_mini_map(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
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

float	ft_raycast(int i, t_cub *cub, int print_ray, int minimap_size)
{
	float	dist;
	float	tmp_dist;
	int		ray_color;

	tmp_dist = 0;
	cub->ray->angle = (cub->player->orient + (-(30 * M_PI / 180)
				+ ((60 * M_PI / 180) / cub->mdata->screen[0]) * i));
	ft_get_direction(cub);
	ft_offset_init(cub);
	dist = ft_dist_to_wall(cub);
	if (print_ray == TRUE)
	{
		while (tmp_dist < dist && tmp_dist < 8)
		{
			ray_color = 0x0D062B;
			cub->ray->x = cub->player->x + tmp_dist * cos(cub->ray->angle);
			cub->ray->y = cub->player->y - tmp_dist * sin(cub->ray->angle);
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
	if (cub->ray->angle <= -M_PI * 0.5 && cub->ray->angle >= -M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle >= M_PI * 0.5 && cub->ray->angle <= M_PI)
		cub->ray->direction = NW;
	else if (cub->ray->angle >= 0 && cub->ray->angle <= M_PI * 0.5)
		cub->ray->direction = NE;
	else if (cub->ray->angle > -M_PI * 0.5 && cub->ray->angle <= 0)
		cub->ray->direction = SE;
	else if (cub->ray->angle > -M_PI && cub->ray->angle <= -M_PI * 0.5)
		cub->ray->direction = SW;
	else if (cub->ray->angle > M_PI)
		cub->ray->direction = SW;
	else if (cub->ray->angle < -M_PI)
		cub->ray->direction = NW;
}
