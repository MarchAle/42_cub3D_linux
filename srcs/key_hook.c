/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/10 13:47:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_hook(int keycode, t_cub *cub)
{
	printf("keycode : %d\n", keycode);
    	// mlx_destroy_image(cub->mlx, cub->img);
	if (keycode == 13)
	{
        cub->player->y -= 0.05;
        // ft_print_map(cub);
		
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
		// printf("x : %f | y : %f\n", cub->player->x, cub->player->y);
	}
	if (keycode == 1)
	{
        cub->player->y += 0.05;
        // ft_print_map(cub);
		
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
		// printf("x : %f | y : %f\n", cub->player->x, cub->player->y);
	}
	if (keycode == 0)
	{
        cub->player->x += 0.05;
        // ft_print_map(cub);
		
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
		// printf("x : %f | y : %f\n", cub->player->x, cub->player->y);
	}
	if (keycode == 2)
	{
        cub->player->x -= 0.05;
        // ft_print_map(cub);
		
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
		// printf("x : %f | y : %f\n", cub->player->x, cub->player->y);
	}
	if (keycode == 53)
		ft_exit(cub);
	return (0);
}
