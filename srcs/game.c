/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/13 14:50:29 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_exit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
	exit(EXIT_SUCCESS);
}

void	ft_mlx_init(t_cub *cub)
{
	cub->mlx->mlx = mlx_init();
	cub->mdata->screen[1] = WIN_HEIGHT;
	cub->mdata->screen[0] = WIN_HEIGHT * WIN_RATIO;
	cub->mlx->win = mlx_new_window(cub->mlx->mlx, cub->mdata->screen[0],
			cub->mdata->screen[1], "Dark3D");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp_divided));
	*(unsigned int *)dst = color;
}
