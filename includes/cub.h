/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 13:42:47 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>

# define BORDER_ERR 0
# define CHAR_ERR 3
# define PLAYER_ERR 4

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

typedef struct s_player
{
    char    direction;
    int     x;
    int     y;
}   t_player;

typedef struct s_cub
{
    struct s_mdata  *mdata;
    struct s_player *player;
    char            **map;
}   t_cub;


#endif