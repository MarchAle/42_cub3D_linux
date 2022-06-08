/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:13:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/08 17:16:18 by dvallien         ###   ########.fr       */
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
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1], "Coubtroider");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    ft_print_img(t_cub *cub)
{
    int x = 0;
    int y = 0;
    t_img   img;

    img.img = mlx_new_image(cub->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (x < cub->mdata->screen[0])
    {
        y = 0;
        while (y < cub->mdata->screen[1])
        {
            // mlx_pixel_put(cub->mlx->mlx, cub->mlx->win, x, y, 9653533 - (x * y / 5));
            if (y == (cub->mdata->screen[1] / 2) + x*2)
                my_mlx_pixel_put(&img, x, y, 0x0000FF);
            if (y == (cub->mdata->screen[1] / 2) - x*2)
                my_mlx_pixel_put(&img, x, y, 9653533);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, img.img, 0, 0);
}

void    ft_print_map(t_cub *cub) // MINI MAP 2D
{
    int x = 0;
    int y = 0;
    t_img   img;

    img.img = mlx_new_image(cub->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (x < (int)ft_strlen(cub->map[1]) * 100)
    {
        y = 0;
        while (y < (int)ft_strlen2d(cub->map) * 100)
        {
            if (cub->map[y / 100][x / 100] == '1')
            {
                my_mlx_pixel_put(&img, x, y, 9653533);
            }
            if (cub->map[y / 100][x / 100] == '0' || cub->map[y / 100][x / 100] == 'N')
            {
                my_mlx_pixel_put(&img, x, y, 8653533);
            }
            if (x >= cub->player->x * 100 - 10 && x <= cub->player->x * 100 + 10 && y >= cub->player->y * 100 - 10 && y <= cub->player->y * 100 + 10)
            {
                my_mlx_pixel_put(&img, x, y, 7653533);   
            }
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, img.img, 0, 0);
}
