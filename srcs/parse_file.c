/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:34:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/03 20:31:03 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_parse_file(char *file, t_cub *cub)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file == -1)
		ft_error(FILE_ERR);
	ft_get_lines(cub, fd_file);
	if (close(fd_file) == -1)
		ft_error(FILE_ERR);
}

void	ft_get_param_from_line(t_cub *cub, char *line)
{
	char	**tmp_line;
	char	*trimed_line;

	if (line[0] != '\n')
	{
		trimed_line = ft_strtrim(line, "\n");
		if (!trimed_line)
			ft_error(MALLOC);
		tmp_line = ft_split(trimed_line, ' ');
		if (!tmp_line)
			ft_error(MALLOC);
		free(trimed_line);
		if (ft_strlen2d(tmp_line) != 2 && ft_strlen(line))
			ft_error(INPUT_ERR);
		ft_get_param(cub, tmp_line);
		ft_split_clear(tmp_line);
	}
}

void	ft_get_lines(t_cub *cub, int fd)
{
	char	*line;
	char	**tmp_line;

	line = get_next_line(fd);
	ft_empty_file(line);
	while (line)
	{
		if (ft_all_params(cub) == 1)
			ft_get_param_from_line(cub, line);
		else
		{
			tmp_line = ft_split(line, ' ');
			ft_get_param(cub, tmp_line);
			ft_split_clear(tmp_line);
			ft_build_map(cub, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (ft_all_params(cub) == 1 || !cub->map)
		ft_error(INPUT_ERR);
}

void	ft_build_map(t_cub *cub, char *line)
{
	int			i;
	char		**tmp_map;

	ft_empty_line_checker(line);
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

int	ft_all_params(t_cub *cub)
{
	if (cub->mdata->no == NULL || cub->mdata->so == NULL
		|| cub->mdata->ea == NULL || cub->mdata->we == NULL
		|| cub->mdata->f == NULL || cub->mdata->c == NULL)
	{
		return (1);
	}
	return (0);
}
