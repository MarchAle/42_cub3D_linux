/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 13:43:26 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_parse_file(char **av, t_cub *cub)
{
	
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata		*mdata;
	t_player	*player;

	// mdata = malloc(sizeof(t_mdata));
	// if (!mdata)
	// 	exit(EXIT_FAILURE);
	cub->mdata = mdata;
	cub->player = player;
}

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
	ft_parse_file(av, cub);
	ft_parse_map(cub);
}