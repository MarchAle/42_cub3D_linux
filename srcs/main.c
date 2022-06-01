/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/01 12:08:40 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int ac, char **av)
{
	t_cub	*cub;
	
    if (ac != 2)
		ft_parse_error(INPUT_ERR);
	ft_go_end_map(av[1]);
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
	cub->map = NULL;
}

void	ft_empty_file(char *line)
{
	if (!line || line[0] == '\n')
		ft_parse_error(INPUT_ERR);
}

void	ft_go_end_map(char *map_cub)
{
	int	i;

	i = 0;
	while (map_cub[i])
		i++;
	ft_check_ext(map_cub, i);
}

void	ft_check_ext(char *map_cub, int i)
{
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