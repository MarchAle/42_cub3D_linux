/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:35:57 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/12 11:30:32 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int 	ft_get_param_split_1(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "NO") == 0)
	{
		if (cub->mdata->no)
			ft_error(INPUT_ERR);
		cub->mdata->no = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->no);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "SO") == 0)
	{
		if (cub->mdata->so)
			ft_error(INPUT_ERR);
		cub->mdata->so = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->so);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "WE") == 0)
	{
		if (cub->mdata->we)
			ft_error(INPUT_ERR);
		cub->mdata->we = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->we);
		return (1);
	}
	return (0);
}

static int	ft_get_param_split_2(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "EA") == 0)
	{
		if (cub->mdata->ea)
			ft_error(INPUT_ERR);
		cub->mdata->ea = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->ea);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "sky") == 0)
	{
		if (cub->mdata->sky)
			ft_error(INPUT_ERR);
		cub->mdata->sky = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->sky);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "floor") == 0)
	{
		if (cub->mdata->floor)
			ft_error(INPUT_ERR);
		cub->mdata->floor = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->floor);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "sprite") == 0)
	{
		if (cub->mdata->sprite)
			ft_error(INPUT_ERR);
		cub->mdata->sprite = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->sprite);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "flashlight") == 0)
	{
		if (cub->mdata->flashlight)
			ft_error(INPUT_ERR);
		cub->mdata->flashlight = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->flashlight);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "door") == 0)
	{
		if (cub->mdata->door)
			ft_error(INPUT_ERR);
		cub->mdata->door = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->door);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "door_locked") == 0)
	{
		if (cub->mdata->door_locked)
			ft_error(INPUT_ERR);
		cub->mdata->door_locked = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->door_locked);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "key") == 0)
	{
		if (cub->mdata->key)
			ft_error(INPUT_ERR);
		cub->mdata->key = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->key);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "potion") == 0)
	{
		if (cub->mdata->potion)
			ft_error(INPUT_ERR);
		cub->mdata->potion = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->potion);
		return (1);
	}
	return (0);
}

void	ft_get_param(t_cub *cub, char **tmp_line)
{
	if (!ft_get_param_split_1(cub, tmp_line)
		&& !ft_get_param_split_2(cub, tmp_line)
		&& !ft_check_colors(cub, tmp_line))
		ft_error(INPUT_ERR);
}

int	ft_check_colors(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "F") == 0)
	{
		cub->mdata->f = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->f);
		return (1);
	}
	if (ft_strcmp(tmp_line[0], "C") == 0)
	{
		cub->mdata->c = ft_split(tmp_line[1], ',');
		ft_get_colors(cub->mdata->c);
		return (1);
	}
	return (0);
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
