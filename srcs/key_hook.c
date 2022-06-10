/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/10 13:48:23 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void	ft_move_player_south(t_cub *cub)
{
	cub->player->x = cub->player->x + 0.05 * cos(cub->player->orientation - M_PI);
	cub->player->y = cub->player->y - 0.05 * sin(cub->player->orientation - M_PI);
}

void	ft_move_player_north(t_cub *cub)
{
	cub->player->x = cub->player->x + 0.05 * cos(cub->player->orientation);
	cub->player->y = cub->player->y - 0.05 * sin(cub->player->orientation);
}

void	ft_move_player_east(t_cub *cub)
{
	cub->player->x = cub->player->x + 0.05 * cos(cub->player->orientation - M_PI * 0.5);
	cub->player->y = cub->player->y - 0.05 * sin(cub->player->orientation - M_PI * 0.5);
}

void	ft_move_player_west(t_cub *cub)
{
	cub->player->x = cub->player->x + 0.05 * cos(cub->player->orientation + M_PI * 0.5);
	cub->player->y = cub->player->y - 0.05 * sin(cub->player->orientation + M_PI * 0.5);
}


int	key_hook(int keycode, t_cub *cub)
{
    // mlx_destroy_image(cub->mlx, cub->img);
	
	if (keycode == 13) // HAUT W
	{
		ft_move_player_north(cub);
        // cub->player->y -= 0.05;
        // ft_print_map(cub);
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	}
	if (keycode == 1) // BAS S
	{
		ft_move_player_south(cub);
        // cub->player->y += 0.05;
        // ft_print_map(cub);
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	}
	if (keycode == 0) // DROITE D
	{
		ft_move_player_east(cub);
        // cub->player->x += 0.05;
        // ft_print_map(cub);
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	}
	if (keycode == 2) // GAUCHE A
	{
		ft_move_player_west(cub);
        // cub->player->x -= 0.05;
        // ft_print_map(cub);
    	// mlx_destroy_image(cub->mlx, cub->img);
		ft_print_view(cub);
    	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	}
	if (keycode == 53)
		ft_exit(cub);
	return (0);
}
