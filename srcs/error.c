/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:03 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 11:43:24 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_parse_error(int type)
{
    if (type == BORDER_ERR)
        ft_putstr_fd("Error : map is not closed", 2);
    exit(EXIT_FAILURE);
}