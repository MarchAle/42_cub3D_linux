/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/02 14:14:19 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_exit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx->win);
	exit(EXIT_SUCCESS);
}

void    ft_mlx_init(t_cub *cub)
{
    cub->mlx->mlx = mlx_init();
    mlx_get_screen_size(cub->mlx->mlx, &cub->mdata->screen[0], &cub->mdata->screen[1]);
    ////
    cub->mdata->screen[1] = 1080;
    cub->mdata->screen[0] = cub->mdata->screen[1] * 5 / 4;
    ////
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1], "Coubtroider");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    ft_mini_map(t_cub *cub)
{
    int x;
    int y;
    int i;
	int	size;
    
	size = MINIMAP_SIZE / cub->mdata->max_size;
    y = 0;
    while (y < (int)ft_strlen2d(cub->map) * size)
    {
        x = 0;
        while (cub->map[y / size] && x < (int)ft_strlen(cub->map[y / size]) * size)
        {
            if (cub->map[y / size][x / size] == '1')
                my_mlx_pixel_put(cub->img, x + 50, y + 30, 0x1a1718);
            if (cub->map[y / size][x / size] == '0' || cub->map[y / size][x / size] == 'N'
                || cub->map[y / size][x / size] == 'S' || cub->map[y / size][x / size] == 'E'
                || cub->map[y / size][x / size] == 'W')
                my_mlx_pixel_put(cub->img, x + 50, y + 30, 0x8c8789);
            x++;
        }
        y++;
    }
    i = cub->mdata->screen[0];
    while (i-- > 0)
        ft_raycast(i, cub, TRUE, size);
}
