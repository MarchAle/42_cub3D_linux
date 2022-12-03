/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:24:46 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/12 11:25:22 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_build_map(t_cub *cub, char *line)
{
	int			i;
	char		**tmp_map;

	ft_empty_line_checker(cub, line);
	i = 0;
	if (line[0] != '\n')
	{
		tmp_map = malloc(sizeof(char *) * (ft_strlen2d(cub->map) + 2));
		if (!tmp_map)
			ft_error(MALLOC);
		while (cub->map && cub->map[i])
		{
			tmp_map[i] = cub->map[i];
			i++;
		}
		tmp_map[i] = ft_strdup(line);
		tmp_map[i + 1] = 0;
		free(cub->map);
		cub->map = tmp_map;
	}
}

void	clean_monster_line(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] != 'X' && line[i] != '\n' && line[i] != ' ')
			line[i] = '0';
		i++;
	}
}

void	fill_surrounding(t_cub *cub, int i, int j)
{
	int x = -1;
	int y;

	while (x <= 1)
	{
		y = -1;
		while (y <= 1)
		{
			if (cub->monster_map[i + x][j + y] && cub->monster_map[i + x][j + y] != ' ' && cub->monster_map[i + x][j + y] != '\n')
				cub->monster_map[i + x][j + y] = 'x';
			y++;
		}
		x++;
	}
}

void	fill_monster_map(t_cub *cub)
{
	int i = 0;
	int j;

	while (cub->monster_map[i])
	{
		j = 0;
		while (cub->monster_map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				cub->map[i][j] = '0';
			if (cub->monster_map[i][j] == 'X')
				fill_surrounding(cub, i, j);
			j++;
		}
		i++;
	}
}

void	print_monster_map(t_cub *cub)
{
	int i = 0;
	while (cub->monster_map[i])
	{
		printf("%s", cub->monster_map[i]);
		i++;
	}
}

void	ft_init_monster_map(t_cub *cub)
{
	int i = 0;

	cub->monster_map = malloc(sizeof(cub->map[0]) * (ft_strlen2d(cub->map)));
	
	while (i < (int)ft_strlen2d(cub->map))
	{
		cub->monster_map[i] = ft_strdup(cub->map[i]);
		clean_monster_line(cub->monster_map[i]);
		i++;
	}
	fill_monster_map(cub);
	// print_monster_map(cub);
}