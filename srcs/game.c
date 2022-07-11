/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/09 14:09:38 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_exit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx->win);
	exit(EXIT_SUCCESS);
}

void	ft_mlx_init(t_cub *cub)
{
	cub->mlx->mlx = mlx_init();
	cub->mdata->screen[1] = 900;
	cub->mdata->screen[0] = cub->mdata->screen[1] * 5 / 4;
	cub->mlx->win = mlx_new_window(cub->mlx->mlx, cub->mdata->screen[0],
			cub->mdata->screen[1], "Dark3D");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
