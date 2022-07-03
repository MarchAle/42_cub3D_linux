/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:35:57 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/03 17:27:36 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void static	ft_get_param_split_1(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "NO") == 0)
	{
		if (cub->mdata->no)
			ft_error(INPUT_ERR);
		cub->mdata->no = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->no);
	}
	if (ft_strcmp(tmp_line[0], "SO") == 0)
	{
		if (cub->mdata->so)
			ft_error(INPUT_ERR);
		cub->mdata->so = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->so);
	}
	if (ft_strcmp(tmp_line[0], "WE") == 0)
	{
		if (cub->mdata->we)
			ft_error(INPUT_ERR);
		cub->mdata->we = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->we);
	}
}

void static	ft_get_param_split_2(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "EA") == 0)
	{
		if (cub->mdata->ea)
			ft_error(INPUT_ERR);
		cub->mdata->ea = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->ea);
	}
	if (ft_strcmp(tmp_line[0], "sky") == 0)
	{
		if (cub->mdata->sky)
			ft_error(INPUT_ERR);
		cub->mdata->sky = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->sky);
	}
	if (ft_strcmp(tmp_line[0], "floor") == 0)
	{
		if (cub->mdata->floor)
			ft_error(INPUT_ERR);
		cub->mdata->floor = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->floor);
	}
}

void	ft_get_param(t_cub *cub, char **tmp_line)
{
	ft_get_param_split_1(cub, tmp_line);
	ft_get_param_split_2(cub, tmp_line);
	ft_check_colors(cub, tmp_line);
}

void	ft_check_colors(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "F") == 0)
	{
		cub->mdata->f = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->f);
	}
	if (ft_strcmp(tmp_line[0], "C") == 0)
	{
		cub->mdata->c = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->c);
	}
}

void	ft_get_colors(char **colors)
{
	int		i;

	i = 0;
	if (ft_strlen2d(colors) != 3)
		ft_error(INPUT_ERR);
	while (colors[i])
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			ft_error(INPUT_ERR);
		i++;
	}
}
