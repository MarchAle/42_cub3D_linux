/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/01 11:34:31 by dvallien         ###   ########.fr       */
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
	cub->map = NULL;
}
