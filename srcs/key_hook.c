/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/08/23 14:21:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_hook_down(int keycode, t_cub *cub)
{
	// printf("%d\n", keycode);
	if (keycode == 65307)
		ft_exit(cub);
	if (keycode == 109)
		cub->minimap *= -1;
	if (keycode == 98)
		cub->blur *= -1;
	if (keycode == 108)
		cub->light *= -1;
	if (keycode == 122)
		cub->move->front = 1;
	if (keycode == 115)
		cub->move->back = 1;
	if (keycode == 113)
		cub->move->left = 1;
	if (keycode == 100)
		cub->move->right = 1;
	if (keycode == 65361)
		cub->move->angle_l = 1;
	if (keycode == 65363)
		cub->move->angle_r = 1;
	if (keycode == 32)
		cub->step = STEP * 1.3;
	return (0);
}

int	key_hook_up(int keycode, t_cub *cub)
{
	if (keycode == 122)
		cub->move->front = 0;
	if (keycode == 115)
		cub->move->back = 0;
	if (keycode == 113)
		cub->move->left = 0;
	if (keycode == 100)
		cub->move->right = 0;
	if (keycode == 65361)
		cub->move->angle_l = 0;
	if (keycode == 65363)
		cub->move->angle_r = 0;
	if (keycode == 32)
		cub->step = STEP;
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
	// pthread_t 	thread = 0;
	if (ft_get_time() - cub->frame_time > 3)
	{
		if (cub->player->health <= 0)
		{
			printf("YOU DIED !\n");
			ft_exit(cub);
		}
		if (cub->player->last_hit > 0)
			cub->player->last_hit--;
		// pthread_create(&thread, NULL, ft_move_monster, (void *)cub);
		// pthread_join(thread, NULL);
		ft_move_monster(cub);

		if (cub->player->last_hit > 7)
			ft_check_collision(cub, cub->player->x - cub->player->kick_x / 3, cub->player->y - cub->player->kick_y / 3);
		// else
		ft_move(cub);
		ft_doors_detection(cub);
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
