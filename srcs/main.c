/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/03 13:08:08 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int ac, char **av)
{
	t_cub	*cub;
	
    if (ac != 2)
		ft_error(INPUT_ERR);
	ft_check_extension(av[1]);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit(EXIT_FAILURE);
	ft_init_struct(cub);
	ft_parse_file(av[1], cub);
	ft_convert_colors(cub);
	ft_parse_map(cub);
	ft_start_game(cub);
}

void	ft_empty_file(char *line)
{
	if (!line || line[0] == '\n')
		ft_error(INPUT_ERR);
}

void	ft_check_extension(char *map_cub)
{
	int	i;

	i = 0;
	while (map_cub[i])
		i++;
	i--;
	if (map_cub[i--] != 'b')
		ft_error(EXT_ERR);
	if (map_cub[i--] != 'u')
		ft_error(EXT_ERR);
	if (map_cub[i--] != 'c')
		ft_error(EXT_ERR);
	if (map_cub[i--] != '.')
		ft_error(EXT_ERR);
}

void	ft_init_orientation(t_cub *cub)
{
	if (cub->player->direction == 'N')
		cub->player->orient = M_PI * 0.5;
	else if (cub->player->direction == 'E')
		cub->player->orient = 0;
	else if (cub->player->direction == 'S')
		cub->player->orient = - M_PI * 0.5;
	else if (cub->player->direction == 'W')
		cub->player->orient = M_PI;
	else
		ft_error(ORIENT);
}

long	ft_get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void    ft_start_game(t_cub *cub)
{
	ft_init_orientation(cub);
    ft_mlx_init(cub);
	ft_init_texture(cub);
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
