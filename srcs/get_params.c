/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:35:57 by dvallien          #+#    #+#             */
/*   Updated: 2022/07/01 20:39:37 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_get_param(t_cub *cub, char **tmp_line)
{
	if (ft_strcmp(tmp_line[0], "NO") == 0)
	{
		if (cub->mdata->NO)
			ft_parse_error(INPUT_ERR);
		cub->mdata->NO = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->NO);
	}
	if (ft_strcmp(tmp_line[0], "SO") == 0)
	{
		if (cub->mdata->SO)
			ft_parse_error(INPUT_ERR);
		cub->mdata->SO = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->SO);
	}
	if (ft_strcmp(tmp_line[0], "WE") == 0)
	{
		if (cub->mdata->WE)
			ft_parse_error(INPUT_ERR);
		cub->mdata->WE = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->WE);
	}
	if (ft_strcmp(tmp_line[0], "EA") == 0)
	{
		if (cub->mdata->EA)
			ft_parse_error(INPUT_ERR);
		cub->mdata->EA = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->EA);
	}
	if (ft_strcmp(tmp_line[0], "sky") == 0)
	{
		if (cub->mdata->sky)
			ft_parse_error(INPUT_ERR);
		cub->mdata->sky = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->sky);
	}
	if (ft_strcmp(tmp_line[0], "floor") == 0)
	{
		if (cub->mdata->floor)
			ft_parse_error(INPUT_ERR);
		cub->mdata->floor = ft_strtrim(tmp_line[1], "\n");
		ft_open_texture(cub->mdata->floor);
	}
	ft_check_colors(cub, tmp_line);
}


void	ft_open_texture(char *dir)
{
	if (open(dir, O_RDONLY) == -1)
	{
		printf("hello %s\n", dir);
		ft_parse_error(INPUT_ERR);
	}
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

int		ft_rgb_to_hex(char **rgb)
{
	// printf("%ld %ld %ld\n", ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	// printf("%ld\n", ((ft_atoi(rgb[0]) & 0xff) << 16) + ((ft_atoi(rgb[1]) & 0xff) << 8) + (ft_atoi(rgb[2]) & 0xff));
	// int nb = ((ft_atoi(rgb[0]) & 0xff) << 16) + ((ft_atoi(rgb[1]) & 0xff) << 8) + (ft_atoi(rgb[2]) & 0xff);
	// printf("r %d\n", (((nb & 0x00ff0000) >> 16)));
	// printf("g %d\n", (((nb & 0x0000ff00) >> 8)));
	// printf("b %d\n", ((nb & 0xff)));
	return ((ft_atoi(rgb[0]) & 0xff) << 16) + ((ft_atoi(rgb[1]) & 0xff) << 8) + (ft_atoi(rgb[2]) & 0xff);
}

// char	**ft_hex_to_rgb(int hex)
// {
// 	char	**rgb;
	
// 	return (rgb);
// }

void	ft_convert_colors(t_cub *cub)
{
	cub->mdata->c_color = ft_rgb_to_hex(cub->mdata->C);
	cub->mdata->f_color = ft_rgb_to_hex(cub->mdata->F);
}
