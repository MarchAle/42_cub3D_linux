/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/09 11:14:28 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int ac, char **av)
{
	t_cub	*cub;
	
    if (ac != 2)
		ft_parse_error(INPUT_ERR);
	ft_check_extension(av[1]);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit(EXIT_FAILURE);
	ft_init_struct(cub);
	ft_parse_file(av[1], cub);
	ft_parse_map(cub);
	ft_start_game(cub);
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata		*mdata;
    t_player	*player;
    t_mlx		*mlx;

    mdata = malloc(sizeof(t_mdata));
    player = malloc(sizeof(t_player));
    mlx = malloc(sizeof(t_mlx));
    if (!mdata || !player || !mlx)
		exit(EXIT_FAILURE);
    cub->mdata = mdata;
    cub->player = player;
	cub->mlx = mlx;
	cub->mdata->NO = NULL;
	cub->mdata->SO = NULL;
	cub->mdata->EA = NULL;
	cub->mdata->WE = NULL;
	cub->mdata->F = NULL;
	cub->mdata->C = NULL;
	cub->map = NULL;
}

void	ft_empty_file(char *line)
{
	if (!line || line[0] == '\n')
		ft_parse_error(INPUT_ERR);
}

void	ft_check_extension(char *map_cub)
{
	int	i;

	i = 0;
	while (map_cub[i])
		i++;
	i--;
	if (map_cub[i--] != 'b')
		ft_parse_error(EXT_ERR);
	if (map_cub[i--] != 'u')
		ft_parse_error(EXT_ERR);
	if (map_cub[i--] != 'c')
		ft_parse_error(EXT_ERR);
	if (map_cub[i--] != '.')
		ft_parse_error(EXT_ERR);
}