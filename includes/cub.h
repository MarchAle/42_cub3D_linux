/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/24 14:29:31 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

typedef struct s_mdata
{
    int     screen[2];
    char    *NO;
    char    *SO;
    char    *EA;
    char    *WE;
    int     F[3];
    int     C[3];
}   t_mdata;


typedef struct s_cub
{
    struct s_mdata  *mdata;
    char            **map;
}   t_cub;


#endif