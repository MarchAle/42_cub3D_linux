/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:41:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 13:45:22 by amarchal         ###   ########.fr       */
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

int	ft_get_color_from_texture(t_texture *tex, int x, int y)
{
	return (*(int *)(tex->addr + (y * tex->line_length + x * (tex->bpp / 8))));
}

int	ft_shade_color(int pix_color, float dist)
{
	int	r;
	int	g;
	int	b;

	if (dist > 3)
	{
		r = ((pix_color & 0x00ff0000) >> 16) * (1 / (1 + (dist - 3)));
		g = ((pix_color & 0x0000ff00) >> 8) * (1 / (1 + (dist - 3)));
		b = (pix_color & 0x000000ff) * (1 / (1 + (dist - 3)));
		return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
	}
	return (pix_color);
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
