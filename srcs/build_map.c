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
