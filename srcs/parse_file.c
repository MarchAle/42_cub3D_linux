/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:34:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/01 14:26:35 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_parse_file(char *file, t_cub *cub)
{
	int	fd_file;
	
	fd_file = open(file, O_RDONLY);
	if(fd_file == -1)
	{
		ft_parse_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}
	ft_get_lines(cub, fd_file);
	if (close(fd_file) == -1)
	{
		ft_parse_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}	
}

void	ft_get_lines(t_cub *cub, int fd)
{
	char	*line;
	char	**tmp_line;

	line = get_next_line(fd);
	ft_empty_file(line);
	while(line)
	{
		if (ft_all_params(cub) == 1)
		{
			tmp_line = ft_split(line, ' ');
			if (tmp_line && ft_strlen2d(tmp_line) != 2 && ft_strlen(line))
				ft_parse_error(INPUT_ERR);
			ft_get_param(cub, tmp_line);
			ft_split_clear(tmp_line);
		}
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
	(void)cub;
}

void	ft_build_map(t_cub *cub, char *line)
{
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (ft_strlen2d(cub->map) + 2));
	while(cub->map && cub->map[i])
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
	if (cub->mdata->NO == NULL || cub->mdata->SO == NULL || cub->mdata->EA == NULL \
		|| cub->mdata->WE == NULL || cub->mdata->F == NULL || cub->mdata->C == NULL)
	{
		return (1);
	}
	return (0);
}


