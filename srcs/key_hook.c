/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/10 17:52:03 by amarchal         ###   ########.fr       */
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

void	ft_move_player(t_cub *cub, int keycode)
{
	if (keycode == 13)
		ft_move_player_north(cub);
	if (keycode == 1)
		ft_move_player_south(cub);
	if (keycode == 0)
		ft_move_player_west(cub);
	if (keycode == 2)
		ft_move_player_east(cub);	
}

void	ft_move_camera(t_cub *cub, int keycode)
{
	if (keycode == 123)
	{
		cub->player->orientation += 0.05;
		if (cub->player->orientation > M_PI)
			cub->player->orientation -= 2 * M_PI;
	}
	if (keycode == 124)
	{
		cub->player->orientation -= 0.05;
		if (cub->player->orientation < - M_PI)
			cub->player->orientation += 2 * M_PI;
	}
}

int	key_hook(int keycode, t_cub *cub)
{
    // mlx_destroy_image(cub->mlx, cub->img);
	if (keycode == 53)
		ft_exit(cub);
	if (keycode == 46)
		cub->minimap *= -1;
	ft_move_player(cub, keycode);
	ft_move_camera(cub, keycode);
	ft_print_view(cub);	
	return (0);
}
