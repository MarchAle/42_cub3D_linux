/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:18:53 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/30 15:18:25 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_move_front(t_cub *cub)
{
	float	target_x;
	float	target_y;

	target_x = cub->player->x + STEP * cos(cub->player->orient);
	target_y = cub->player->y - STEP * sin(cub->player->orient);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_back(t_cub *cub)
{
	float	target_x;
	float	target_y;

	target_x = cub->player->x + STEP * cos(cub->player->orient - M_PI);
	target_y = cub->player->y - STEP * sin(cub->player->orient - M_PI);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_right(t_cub *cub)
{
	float	target_x;
	float	target_y;

	target_x = cub->player->x + STEP * cos(cub->player->orient - M_PI * 0.5);
	target_y = cub->player->y - STEP * sin(cub->player->orient - M_PI * 0.5);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_left(t_cub *cub)
{
	float	target_x;
	float	target_y;

	target_x = cub->player->x + STEP * cos(cub->player->orient + M_PI * 0.5);
	target_y = cub->player->y - STEP * sin(cub->player->orient + M_PI * 0.5);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_camera(t_cub *cub, int dir)
{
	if (dir == RIGHT)
	{
		cub->player->orient += STEP;
		if (cub->player->orient > M_PI)
			cub->player->orient -= 2 * M_PI;
	}
	if (dir == LEFT)
	{
		cub->player->orient -= STEP;
		if (cub->player->orient < - M_PI)
			cub->player->orient += 2 * M_PI;
	}
}
