/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/29 17:36:36 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_move_allowed(t_cub *cub, float x, float y)
{
	if (cub->map[(int)floor(cub->player->y)][(int)floor(x)] != '1')
	{
		if (x - (int)floor(x) >= (1 - STEP) && cub->map[(int)floor(cub->player->y)][(int)floor(x) + 1] == '1')
			cub->player->x = (int)floor(cub->player->x) + (1 - STEP);
		else if (x - (int)floor(x) <= STEP && cub->map[(int)floor(cub->player->y)][(int)floor(x) - 1] == '1')
			cub->player->x = (int)floor(cub->player->x) + STEP;	
		else
			cub->player->x = x;
	}
	else
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
	if (cub->map[(int)floor(y)][(int)floor(cub->player->x)] != '1')
	{
		if (y - (int)floor(y) >= (1 - STEP) && cub->map[(int)floor(y) + 1][(int)floor(cub->player->x)] == '1') 
			cub->player->y = (int)floor(cub->player->y) + (1 - STEP);
		else if (y - (int)floor(y) <= STEP && cub->map[(int)floor(y) - 1][(int)floor(cub->player->x)] == '1')
			cub->player->y = (int)floor(cub->player->y) + STEP;
		else	
			cub->player->y = y;
	}
	else
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
}

void	ft_move_player_south(t_cub *cub)
{
	ft_move_allowed(cub, cub->player->x + STEP * cos(cub->player->orientation - M_PI), cub->player->y - STEP * sin(cub->player->orientation - M_PI));
	// cub->player->x = cub->player->x + STEP * cos(cub->player->orientation - M_PI);
	// cub->player->y = cub->player->y - STEP * sin(cub->player->orientation - M_PI);
}

void	ft_move_player_north(t_cub *cub)
{
	ft_move_allowed(cub, cub->player->x + STEP * cos(cub->player->orientation), cub->player->y - STEP * sin(cub->player->orientation));
	// cub->player->x = cub->player->x + STEP * cos(cub->player->orientation);
	// cub->player->y = cub->player->y - STEP * sin(cub->player->orientation);
}

void	ft_move_player_east(t_cub *cub)
{
	ft_move_allowed(cub, cub->player->x + STEP * cos(cub->player->orientation - M_PI * 0.5), cub->player->y - STEP * sin(cub->player->orientation - M_PI * 0.5));
	// cub->player->x = cub->player->x + STEP * cos(cub->player->orientation - M_PI * 0.5);
	// cub->player->y = cub->player->y - STEP * sin(cub->player->orientation - M_PI * 0.5);
}

void	ft_move_player_west(t_cub *cub)
{
	ft_move_allowed(cub, cub->player->x + STEP * cos(cub->player->orientation + M_PI * 0.5), cub->player->y - STEP * sin(cub->player->orientation + M_PI * 0.5));
	// cub->player->x = cub->player->x + STEP * cos(cub->player->orientation + M_PI * 0.5);
	// cub->player->y = cub->player->y - STEP * sin(cub->player->orientation + M_PI * 0.5);
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
		cub->player->orientation += STEP;
		if (cub->player->orientation > M_PI)
			cub->player->orientation -= 2 * M_PI;
	}
	if (keycode == 124)
	{
		cub->player->orientation -= STEP;
		if (cub->player->orientation < - M_PI)
			cub->player->orientation += 2 * M_PI;
	}
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 53)
		ft_exit(cub);
	if (keycode == 46)
		cub->minimap *= -1;
	ft_move_player(cub, keycode);
	ft_move_camera(cub, keycode);
	ft_print_view(cub);	
	return (0);
}
