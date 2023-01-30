/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:41:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/09/30 15:31:59 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_rgb_to_hex(char **rgb)
{
	return (((ft_atoi(rgb[0]) & 0xff) << 16) + ((ft_atoi(rgb[1]) & 0xff) << 8)
		+ (ft_atoi(rgb[2]) & 0xff));
}

void	ft_convert_colors(t_cub *cub)
{
	cub->mdata->c_color = ft_rgb_to_hex(cub->mdata->c);
	cub->mdata->f_color = ft_rgb_to_hex(cub->mdata->f);
	ft_split_clear(cub->mdata->c);
	ft_split_clear(cub->mdata->f);
}

int	ft_get_color_from_img(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8))));
}

int	ft_get_color_from_texture(t_texture *tex, int x, int y)
{
	return (*(int *)(tex->addr + (y * tex->line_length + x * (tex->bpp / 8))));
}

float	ft_flashlight(t_cub *cub, float dist, int i, int j, int object)
{
	float corrected_dist;
	float vignet = sqrtf(powf(cub->calc->half_height - j, 2) + powf(cub->calc->half_width - i, 2));

	if (dist < 1.5)
		corrected_dist = 0;
	else
		corrected_dist = (dist - 1.5) * 2.3;
	vignet = vignet / cub->calc->max_vignet;
	if (dist < 1 && (object == WALL || object == MONSTER))
		vignet = vignet - (vignet - ((dist) / 1 * vignet));
	if (vignet > 0.3)
		corrected_dist += (vignet - 0.3) * 8;
	else if (vignet < 0.1)
		corrected_dist -= corrected_dist * 0.75;
	else
		corrected_dist -= corrected_dist * (1.125 - 3.75 * vignet);
	return (corrected_dist * cub->light_intens);
	(void)object;
}

int	ft_shade_color(int pix_color, float dist)
{
	int	r;
	int	g;
	int	b;

	r = ((pix_color & 0x00ff0000) >> 16) * (1 / (1 + (dist)));
	g = ((pix_color & 0x0000ff00) >> 8) * (1 / (1 + (dist)));
	b = (pix_color & 0x000000ff) * (1 / (1 + (dist)));
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	ft_fade_color(int pix_color, float dist)
{
	int	r;
	int	g;
	int	b;

	r = ((pix_color & 0x00ff0000) >> 16) * (dist * 10.77 / 8);
	g = ((pix_color & 0x0000ff00) >> 8) * (dist * 22.5 / 8);
	b = (pix_color & 0x000000ff) * (dist * 3.19 / 8);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
