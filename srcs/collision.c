/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:16:56 by amarchal          #+#    #+#             */
/*   Updated: 2022/09/30 15:56:08 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_move_x(t_cub *cub, float x)
{
	if (x - (int)floor(x) >= (1 - STEP)
		&& (cub->map[(int)floor(cub->player->y)][(int)floor(x) + 1] == '1' || (cub->map[(int)floor(cub->player->y)][(int)floor(x) + 1] == 'D' && cub->player->door_open == 0)))
		cub->player->x = (int)floor(cub->player->x) + (1 - STEP);
	else if (x - (int)floor(x) <= STEP
		&& (cub->map[(int)floor(cub->player->y)][(int)floor(x) - 1] == '1' || (cub->map[(int)floor(cub->player->y)][(int)floor(x) - 1] == 'D' && cub->player->door_open == 0)))
		cub->player->x = (int)floor(cub->player->x) + STEP;
	else
		cub->player->x = x;
}

void	ft_wall_gap_x(t_cub *cub, float x)
{
	if ((int)floor(x) > (int)floor(cub->player->x))
	{
		if ((int)floor(cub->player->x) + (1 - STEP) < cub->player->x)
			cub->player->x = (int)floor(cub->player->x) + (1 - STEP);
	}
	else if ((int)floor(x) < (int)floor(cub->player->x))
	{
		if ((int)floor(cub->player->x) + STEP > cub->player->x)
			cub->player->x = (int)floor(cub->player->x) + STEP;
	}
	else
		cub->player->x = x;
}

void	ft_move_y(t_cub *cub, float y)
{
	if (y - (int)floor(y) >= (1 - STEP)
		&& (cub->map[(int)floor(y) + 1][(int)floor(cub->player->x)] == '1' || (cub->map[(int)floor(y) + 1][(int)floor(cub->player->x)] == 'D' && cub->player->door_open == 0)))
		cub->player->y = (int)floor(cub->player->y) + (1 - STEP);
	else if (y - (int)floor(y) <= STEP
		&& (cub->map[(int)floor(y) - 1][(int)floor(cub->player->x)] == '1' || (cub->map[(int)floor(y) - 1][(int)floor(cub->player->x)] == 'D' && cub->player->door_open == 0)))
		cub->player->y = (int)floor(cub->player->y) + STEP;
	else
		cub->player->y = y;
}

void	ft_wall_gap_y(t_cub *cub, float y)
{
	if ((int)floor(y) > (int)floor(cub->player->y))
	{
		if ((int)floor(cub->player->y) + (1 - STEP) < cub->player->y)
			cub->player->y = (int)floor(cub->player->y) + (1 - STEP);
	}
	else if ((int)floor(y) < (int)floor(cub->player->y))
	{
		if ((int)floor(cub->player->y) + STEP > cub->player->y)
			cub->player->y = (int)floor(cub->player->y) + STEP;
	}
	else
		cub->player->y = y;
}

void	ft_check_collision(t_cub *cub, float x, float y)
{
	if ((cub->map[(int)floor(cub->player->y)][(int)floor(x)] != '1' && cub->map[(int)floor(cub->player->y)][(int)floor(x)] != 'D') || (cub->map[(int)floor(cub->player->y)][(int)floor(x)] == 'D' && cub->player->door_open == 1))
		ft_move_x(cub, x);
	else
		ft_wall_gap_x(cub, x);
	if ((cub->map[(int)floor(y)][(int)floor(cub->player->x)] != '1' && cub->map[(int)floor(y)][(int)floor(cub->player->x)] != 'D') || (cub->map[(int)floor(y)][(int)floor(cub->player->x)] == 'D' && cub->player->door_open == 1))
		ft_move_y(cub, y);
	else
		ft_wall_gap_y(cub, y);
}
