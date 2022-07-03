/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:18:53 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 17:15:11 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_move_front(t_cub *cub)
{
	float	target_x;
	float	target_y;

	ft_acceleration(&cub->move->front, &cub->move->front_a, MOVE);
	target_x = cub->player->x + (cub->move->front_a * cub->step / ACCEL)
		* cos(cub->player->orient);
	target_y = cub->player->y - (cub->move->front_a * cub->step / ACCEL)
		* sin(cub->player->orient);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_back(t_cub *cub)
{
	float	target_x;
	float	target_y;

	ft_acceleration(&cub->move->back, &cub->move->back_a, MOVE);
	target_x = cub->player->x + (cub->move->back_a * cub->step / ACCEL)
		* cos(cub->player->orient - M_PI);
	target_y = cub->player->y - (cub->move->back_a * cub->step / ACCEL)
		* sin(cub->player->orient - M_PI);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_right(t_cub *cub)
{
	float	target_x;
	float	target_y;

	ft_acceleration(&cub->move->right, &cub->move->right_a, MOVE);
	target_x = cub->player->x + (cub->move->right_a * cub->step / ACCEL)
		* cos(cub->player->orient - M_PI * 0.5);
	target_y = cub->player->y - (cub->move->right_a * cub->step / ACCEL)
		* sin(cub->player->orient - M_PI * 0.5);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_left(t_cub *cub)
{
	float	target_x;
	float	target_y;

	ft_acceleration(&cub->move->left, &cub->move->left_a, MOVE);
	target_x = cub->player->x + (cub->move->left_a * cub->step / ACCEL)
		* cos(cub->player->orient + M_PI * 0.5);
	target_y = cub->player->y - (cub->move->left_a * cub->step / ACCEL)
		* sin(cub->player->orient + M_PI * 0.5);
	ft_check_collision(cub, target_x, target_y);
}

void	ft_move_camera(t_cub *cub, int dir)
{
	if (dir == RIGHT)
	{
		ft_acceleration(&cub->move->angle_r, &cub->move->angle_r_a, CAMERA);
		cub->player->orient -= (cub->move->angle_r_a * cub->step / O_ACC);
		if (cub->player->orient < -M_PI)
			cub->player->orient += 2 * M_PI;
	}
	if (dir == LEFT)
	{
		ft_acceleration(&cub->move->angle_l, &cub->move->angle_l_a, CAMERA);
		cub->player->orient += (cub->move->angle_l_a * cub->step / O_ACC);
		if (cub->player->orient > M_PI)
			cub->player->orient -= 2 * M_PI;
	}
}
