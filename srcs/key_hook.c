/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:44:30 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/06 10:08:31 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 13)
	{
        cub->player->y -= 0.05;
        ft_print_map(cub);
	}
	if (keycode == 1)
	{
        cub->player->y += 0.05;
        ft_print_map(cub);
	}
	if (keycode == 0)
	{
        cub->player->x -= 0.05;
        ft_print_map(cub);
	}
	if (keycode == 2)
	{
        cub->player->x += 0.05;
        ft_print_map(cub);
	}
	if (keycode == 53)
		ft_exit(cub);
	return (0);
}
