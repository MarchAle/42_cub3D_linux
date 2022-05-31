/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 17:35:59 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int ac, char **av)
{
	t_cub	*cub;
	
    if (ac != 2)
	{
		ft_putstr_fd("Error : invalid number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit(EXIT_FAILURE);
	ft_init_struct(cub);
	ft_parse_file(av[1], cub);
	ft_parse_map(cub);
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata     *mdata;
    t_player    *player;

    mdata = malloc(sizeof(t_mdata));
    player = malloc(sizeof(t_player));
    if (!mdata)
     exit(EXIT_FAILURE);
    cub->mdata = mdata;
    cub->player = player;
	cub->mdata->NO = NULL;
	cub->mdata->SO = NULL;
	cub->mdata->EA = NULL;
	cub->mdata->WE = NULL;
	cub->mdata->F = NULL;
	cub->mdata->C = NULL;
}

void	ft_parse_file(char *file, t_cub *cub)
{
	int	fd_file;
	
	fd_file = open(file, O_RDONLY);
	if(fd_file == -1)
	{
		ft_parse_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}
	ft_init_map(cub, fd_file);
	if (close(fd_file) == -1)
	{
		ft_parse_error(FILE_ERR);
		exit(EXIT_FAILURE);
	}	
}

void	ft_init_map(t_cub *cub, int fd)
{
	int		i;
	char	*line;
	char	**tmp_line;
	(void)cub;

	i = 0;
	line = get_next_line(fd);
	while(line)
	{
		if (ft_params(cub)) // je vérifie si j'ai recupere tous les param dans la struct cud->mdata
		{
			tmp_line = ft_split(line, ' ');
			if (tmp_line && ft_strlen2d(tmp_line) != 2 && ft_strlen(line))
				ft_parse_error(INPUT_ERR);
			ft_get_param(cub, tmp_line);
			// free tmp_line;
		}
		else
		{
			// ft_je_cree_la_map_2d(line)
		}
		free(line);
		line = get_next_line(fd);
	}
}

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
