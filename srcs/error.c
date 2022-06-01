/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:03 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/01 12:08:35 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_parse_error(int type)
{
    if (type == BORDER_ERR)
        ft_putstr_fd("Error : map is not closed", 2);
    if (type == FILE_ERR)
        ft_putstr_fd("Error : file error", 2);
    if (type == INPUT_ERR)
        ft_putstr_fd("Error : invalid input", 2);
    if (type == EXT_ERR)
        ft_putstr_fd("Error : bad map extension", 2);
    exit(EXIT_FAILURE);
}