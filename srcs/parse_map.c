/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:45:53 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/06 10:23:08 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    ft_check_char(char c, int x, int y, t_cub *cub)
{
    static  int  nb_player = 0;

    if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
        ft_parse_error(CHAR_ERR);
    else
    {
        cub->player->direction = c;
        cub->player->x = x + 0.5;
        cub->player->y = y + 0.5;
        cub->player->offset_x = 0.5;
        cub->player->offset_y = 0.5;
        if (nb_player == 0)
            nb_player++;
        else
            ft_parse_error(PLAYER_ERR); // if there are more than one player, return error
    }
}

void    ft_check_border(char **map, int x, int y)
{
    if (!map[y][x - 1] || map[y][x - 1] == ' ' || map[y][x - 1] == '\n')
        ft_parse_error(BORDER_ERR);
    if (!map[y][x + 1] || map[y][x + 1] == ' ' || map[y][x + 1] == '\n')
        ft_parse_error(BORDER_ERR);
    if (!map[y - 1] || !map[y - 1][x] || map[y - 1][x] == ' ' || map[y - 1][x] == '\n')
        ft_parse_error(BORDER_ERR);
    if (!map[y + 1] || !map[y + 1][x] || map[y + 1][x] == ' ' || map[y + 1][x] == '\n')
        ft_parse_error(BORDER_ERR);
}

void    ft_check_line(char *line, int y, char **map, t_cub *cub)
{
    int x;

    x = 0;
    while (line[x] && line[x] != '\n') // 
    {
        if (line[x] != '1' && line[x] != ' ')
            ft_check_border(map, x, y);
        if (line[x] != '1' && line[x] != ' ' && line[x] != '0')
            ft_check_char(line[x], x, y, cub);
        x++;
    }
}

void    ft_parse_map(t_cub *cub)
{
    char **map = cub->map;
    int y;

    y = 0;
    cub->player->direction = '\0';
    while (map[y])
    {
        ft_check_line(map[y], y, map, cub);
        y++;
    }
    if (cub->player->direction == '\0')
        ft_parse_error(PLAYER_ERR); // if there is no player, return error
}
