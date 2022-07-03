/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acceleration.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:14:52 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 17:15:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_acceleration(int	*dir, int *accel, int type)
{
	int	acc;

	if (type == MOVE)
		acc = ACCEL;
	else
		acc = O_ACC;
	if (*dir)
	{
		if (*accel < acc)
			*accel += 1;
	}
	else
	{
		if (*accel > 0)
			*accel -= 1;
	}
}
