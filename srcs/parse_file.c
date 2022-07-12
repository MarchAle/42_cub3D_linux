/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:34:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/12 11:30:22 by amarchal         ###   ########.fr       */
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

void	ft_extra_param_or_build(t_cub *cub, char *line)
{
	char	**tmp_line;

	tmp_line = ft_split(line, ' ');
	if (ft_strcmp(tmp_line[0], "sky") && ft_strcmp(tmp_line[0], "floor"))
		ft_build_map(cub, line);
	else if (cub->mdata->start_build == 0)
		ft_get_param(cub, tmp_line);
	else
		ft_error(INPUT_ERR);
	ft_split_clear(tmp_line);
}

void	ft_get_lines(t_cub *cub, int fd)
{
	char	*line;

	line = get_next_line(fd);
	ft_empty_file(line);
	while (line)
	{
		if (ft_all_params(cub) == 1)
			ft_get_param_from_line(cub, line);
		else
			ft_extra_param_or_build(cub, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (ft_all_params(cub) == 1 || !cub->map)
		ft_error(INPUT_ERR);
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
