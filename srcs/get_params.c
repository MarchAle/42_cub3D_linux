/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:35:57 by dvallien          #+#    #+#             */
/*   Updated: 2022/06/01 11:36:17 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_get_param(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "NO") == 0)
	{
		if (cub->mdata->NO)
			ft_parse_error(INPUT_ERR);
		cub->mdata->NO = tmp_line[1];
		ft_open_texture(cub->mdata->NO);
	}
	if (ft_strcmp(tmp_line[0], "SO") == 0)
	{
		if (cub->mdata->SO)
			ft_parse_error(INPUT_ERR);
		cub->mdata->SO = tmp_line[1];
		ft_open_texture(cub->mdata->SO);
	}
	if (ft_strcmp(tmp_line[0], "WE") == 0)
	{
		if (cub->mdata->WE)
			ft_parse_error(INPUT_ERR);
		cub->mdata->WE = tmp_line[1];
		ft_open_texture(cub->mdata->WE);
	}
	if (ft_strcmp(tmp_line[0], "EA") == 0)
	{
		if (cub->mdata->EA)
			ft_parse_error(INPUT_ERR);
		cub->mdata->EA = tmp_line[1];
		ft_open_texture(cub->mdata->EA);
	}
	ft_check_colors(cub, tmp_line);
}


void	ft_open_texture(char *dir)
{
	(void)dir;
	// if (open(dir, O_RDONLY) == -1)
	// 	ft_parse_error(INPUT_ERR_TEST);
}

void	ft_check_colors(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "F") == 0)
	{
		cub->mdata->F = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->F);
	}
	if (ft_strcmp(tmp_line[0], "C") == 0)
	{
		cub->mdata->C = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->C);
	}
}

void	ft_get_colors(char **colors)
{
	int		i;
	
	i = 0;
	if (ft_strlen2d(colors) != 3)
		ft_parse_error(INPUT_ERR);
	while (colors[i])
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			ft_parse_error(INPUT_ERR);
		i++;
	}
}
