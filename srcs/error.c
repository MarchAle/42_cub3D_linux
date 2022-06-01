/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:03 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/01 13:08:53 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_parse_error(int type)
{
    if (type == FILE_ERR)
        ft_putstr_fd("Error : file error\n", 2);
    if (type == INPUT_ERR)
        ft_putstr_fd("Error : invalid input\n", 2);
    if (type == BORDER_ERR)
        ft_putstr_fd("Error : map is not closed\n", 2);
    if (type == CHAR_ERR)
        ft_putstr_fd("Error : forbidden char\n", 2);
    if (type == PLAYER_ERR)
        ft_putstr_fd("Error : should be one player\n", 2);
    exit(EXIT_FAILURE);
}