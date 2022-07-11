/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 15:14:51 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_hook_down(int keycode, t_cub *cub)
{
	if (keycode == 53)
		ft_exit(cub);
	if (keycode == 46)
		cub->minimap *= -1;
	if (keycode == 13)
		cub->move->front = 1;
	if (keycode == 1)
		cub->move->back = 1;
	if (keycode == 0)
		cub->move->left = 1;
	if (keycode == 2)
		cub->move->right = 1;
	if (keycode == 123)
		cub->move->angle_l = 1;
	if (keycode == 124)
		cub->move->angle_r = 1;
	if (keycode == 49)
		cub->step = 0.08;
	return (0);
}

int	key_hook_up(int keycode, t_cub *cub)
{
	if (keycode == 13)
		cub->move->front = 0;
	if (keycode == 1)
		cub->move->back = 0;
	if (keycode == 0)
		cub->move->left = 0;
	if (keycode == 2)
		cub->move->right = 0;
	if (keycode == 123)
		cub->move->angle_l = 0;
	if (keycode == 124)
		cub->move->angle_r = 0;
	if (keycode == 49)
		cub->step = 0.05;
	return (0);
}

void	ft_position_update(t_cub *cub)
{
	if (cub->player->x - floor(cub->player->x) == 0)
		cub->player->x -= 0.000001;
	if (cub->player->y - floor(cub->player->y) == 0)
		cub->player->y -= 0.000001;
}

void	ft_move(t_cub *cub)
{
	if ((cub->move->front == 1 && cub->move->back == 0)
		|| cub->move->front_a)
		ft_move_front(cub);
	if ((cub->move->front == 0 && cub->move->back == 1)
		|| cub->move->back_a)
		ft_move_back(cub);
	if ((cub->move->right == 1 && cub->move->left == 0)
		|| cub->move->right_a)
		ft_move_right(cub);
	if ((cub->move->right == 0 && cub->move->left == 1)
		|| cub->move->left_a)
		ft_move_left(cub);
	if ((cub->move->angle_l == 1 && cub->move->angle_r == 0)
		|| cub->move->angle_l_a)
		ft_move_camera(cub, LEFT);
	if ((cub->move->angle_l == 0 && cub->move->angle_r == 1)
		|| cub->move->angle_r_a)
		ft_move_camera(cub, RIGHT);
}

int	ft_loop_move(t_cub *cub)
{
	if (ft_get_time() - cub->frame_time > 3)
	{
		ft_move(cub);
		ft_position_update(cub);
		ft_print_view(cub);
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			30, 50, 0x934d1d, "press space to run");
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			30, 70, 0x934d1d, "press M for minimap");
		cub->frame_time = ft_get_time();
	}
	ft_fps(cub);
	return (0);
}
