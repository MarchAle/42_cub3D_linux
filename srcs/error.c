/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:03 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 17:01:13 by dvallien         ###   ########.fr       */
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
    if (type == INPUT_ERR_TEST)
        ft_putstr_fd("Error : TEST", 2);
    exit(EXIT_FAILURE);
}