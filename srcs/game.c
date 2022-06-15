/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/15 13:50:29 by amarchal         ###   ########.fr       */
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
    cub->mdata->screen[1] = 720;
    cub->mdata->screen[0] = cub->mdata->screen[1] * 16 / 9;
    ////
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1], "Coubtroider");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    ft_mini_map(t_cub *cub) // MINI MAP 2D
{
    int x;
    int y;
    int i;
    char **wall_color;
    char **tile_color;

    wall_color = ft_split("79,72,71", ',');
    tile_color = ft_split("245,228,225", ',');
    
    x = 0;
    while (x < (int)ft_strlen(cub->map[1]) * 25)
    {
        y = 0;
        while (y < (int)ft_strlen2d(cub->map) * 25)
        {
            if (cub->map[y / 25][x / 25] == '1')
                my_mlx_pixel_put(cub->img, x + 50, y + 30, 0x4f484773);
            if (cub->map[y / 25][x / 25] == '0' || cub->map[y / 25][x / 25] == 'N'
                || cub->map[y / 25][x / 25] == 'S' || cub->map[y / 25][x / 25] == 'E'
                || cub->map[y / 25][x / 25] == 'W')
                my_mlx_pixel_put(cub->img, x + 50, y + 30, 0xf5e4e173);
            y++;
        }
        x++;
    }
    i = cub->mdata->screen[0];
    while (i-- > 0)
        ft_raycast(i, cub, TRUE);
}

