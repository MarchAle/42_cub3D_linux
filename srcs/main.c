/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/30 11:21:39 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int ac, char **av)
{
	t_cub	*cub;
	
    if (ac != 2)
	{
		ft_putstr_fd("Error : invalid number of arguments", 1);
		exit(EXIT_FAILURE);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit(EXIT_FAILURE);
	ft_init_struct(cub);
	ft_parse_map(av, cub);
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata	*mdata;

	mdata = malloc(sizeof(t_mdata));
	if (!mdata)
		exit(EXIT_FAILURE);
	cub->mdata = mdata;
}

void	ft_parse_map(char **av, t_cub *cub)
{
	
}