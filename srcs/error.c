/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:03 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 16:56:14 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_error(int type)
{
	if (type == FILE_ERR)
		ft_putstr_fd("Error : cannot open file\n", 2);
	if (type == INPUT_ERR)
		ft_putstr_fd("Error : invalid input\n", 2);
	if (type == EXT_ERR)
		ft_putstr_fd("Error : invalid file extension\n", 2);
	if (type == BORDER_ERR)
		ft_putstr_fd("Error : map is not closed\n", 2);
	if (type == CHAR_ERR)
		ft_putstr_fd("Error : forbidden char\n", 2);
	if (type == PLAYER_ERR)
		ft_putstr_fd("Error : should be one player\n", 2);
	if (type == MALLOC)
		ft_putstr_fd("Error : memory allocation failed\n", 2);
	if (type == ORIENT)
		ft_putstr_fd("Error : init orientation failed\n", 2);
	if (type == OPEN)
		ft_putstr_fd("Error : access denied to texture file\n", 2);
	if (type == EMPTY_LINE)
		ft_putstr_fd("Error : empty line in map\n", 2);
	exit(EXIT_FAILURE);
}
