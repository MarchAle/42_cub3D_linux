/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:34:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/03 17:26:29 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_parse_file(char *file, t_cub *cub)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file == -1)
	{
		ft_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}
	ft_get_lines(cub, fd_file);
	if (close(fd_file) == -1)
	{
		ft_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}	
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
}

void	ft_build_map(t_cub *cub, char *line)
{
	int			i;
	char		**tmp_map;
	static int	start_build = 0;
	static int	empty_line = 0;

	if (empty_line != 0 && line[0] != '\n')
		ft_error(EMPTY_LINE);
	if (line[0] != '\n' && start_build == 0)
		start_build = 1;
	if (start_build == 1 && line[0] == '\n')
		empty_line = 1;
	i = 0;
	tmp_map = malloc(sizeof(char *) * (ft_strlen2d(cub->map) + 2));
	while (cub->map && cub->map[i])
	{
		tmp_map[i] = cub->map[i];
		i++;
	}
	tmp_map[i] = ft_strdup(line);
	tmp_map[i + 1] = 0;
	cub->map = tmp_map;
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
