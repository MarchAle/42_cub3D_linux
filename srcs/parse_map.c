/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:45:53 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 10:24:51 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_check_char(char c, int x, int y, t_cub *cub)
{
	static int	nb_player = 0;

	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		ft_error(CHAR_ERR);
	else
	{
		cub->player->direction = c;
		cub->player->x = x + 0.5;
		cub->player->y = y + 0.5;
		if (nb_player == 0)
			nb_player++;
		else
			ft_error(PLAYER_ERR);
	}
}

void	ft_check_border(char **map, int x, int y)
{
	if (!map[y][x - 1] || map[y][x - 1] == ' ' || map[y][x - 1] == '\n')
		ft_error(BORDER_ERR);
	if (!map[y][x + 1] || map[y][x + 1] == ' ' || map[y][x + 1] == '\n')
		ft_error(BORDER_ERR);
	if (!map[y - 1] || !map[y - 1][x] || map[y - 1][x] == ' '
		|| map[y - 1][x] == '\n')
		ft_error(BORDER_ERR);
	if (!map[y + 1] || !map[y + 1][x] || map[y + 1][x] == ' '
		|| map[y + 1][x] == '\n')
		ft_error(BORDER_ERR);
}

void	ft_check_line(char *line, int y, char **map, t_cub *cub)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		if (line[x] != '1' && line[x] != ' ')
			ft_check_border(map, x, y);
		if (line[x] != '1' && line[x] != ' ' && line[x] != '0')
			ft_check_char(line[x], x, y, cub);
		x++;
	}
	if (x - 1 > cub->mdata->max_size)
		cub->mdata->max_size = x - 1;
}

void	ft_parse_map(t_cub *cub)
{
	char	**map;
	int		y;

	map = cub->map;
	y = 0;
	cub->mdata->max_size = 0;
	cub->player->direction = '\0';
	while (map[y])
	{
		ft_check_line(map[y], y, map, cub);
		y++;
	}
	if (y - 1 > cub->mdata->max_size)
		cub->mdata->max_size = y - 1;
	if (cub->player->direction == '\0')
		ft_error(PLAYER_ERR);
}
