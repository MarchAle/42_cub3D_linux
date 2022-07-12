/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/11 16:20:11 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_orientation(t_cub *cub)
{
	if (cub->player->direction == 'N')
		cub->player->orient = M_PI * 0.5;
	else if (cub->player->direction == 'E')
		cub->player->orient = 0;
	else if (cub->player->direction == 'S')
		cub->player->orient = -M_PI * 0.5;
	else if (cub->player->direction == 'W')
		cub->player->orient = M_PI;
	else
		ft_error(ORIENT);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		ft_error(INPUT_ERR);
	ft_check_extension(av[1], "cub");
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit(EXIT_FAILURE);
	ft_init_struct(cub);
	ft_parse_file(av[1], cub);
	ft_convert_colors(cub);
	ft_parse_map(cub);
	ft_init_orientation(cub);
	ft_mlx_init(cub);
	ft_init_texture(cub);
	ft_start_game(cub);
}

void	ft_empty_file(char *line)
{
	if (!line)
		ft_error(INPUT_ERR);
}

void	ft_start_game(t_cub *cub)
{
	cub->step = 0.05;
	cub->minimap = -1;
	cub->frames = 0;
	cub->fps_time = ft_get_time();
	cub->frame_time = ft_get_time();
	ft_print_view(cub);
	mlx_hook(cub->mlx->win, 17, 0, ft_exit, cub);
	mlx_hook(cub->mlx->win, 2, 0, key_hook_down, cub);
	mlx_hook(cub->mlx->win, 3, 0, key_hook_up, cub);
	mlx_loop_hook(cub->mlx->mlx, ft_loop_move, cub);
	mlx_loop(cub->mlx->mlx);
}
