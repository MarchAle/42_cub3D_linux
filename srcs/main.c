/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/01 20:39:17 by amarchal         ###   ########.fr       */
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
	ft_convert_colors(cub);
	ft_parse_map(cub);
	ft_start_game(cub);
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata		*mdata;
    t_player	*player;
    t_mlx		*mlx;
	t_ray		*ray;
	t_texture	*north;
	t_texture	*east;
	t_texture	*south;
	t_texture	*west;
	t_texture	*sky;
	t_texture	*floor;
	t_move		*move;
    
    mdata = malloc(sizeof(t_mdata));
    player = malloc(sizeof(t_player));
    mlx = malloc(sizeof(t_mlx));
	ray = malloc(sizeof(t_ray));
	north = malloc(sizeof(t_texture));
	east = malloc(sizeof(t_texture));
	south = malloc(sizeof(t_texture));
	west = malloc(sizeof(t_texture));
	sky = malloc(sizeof(t_texture));
	floor = malloc(sizeof(t_texture));
	move = malloc(sizeof(t_move));
    if (!mdata || !player || !mlx || !ray || !north || !move || !sky || !floor)
		exit(EXIT_FAILURE);
    cub->mdata = mdata;
    cub->player = player;
	cub->mlx = mlx;
    cub->ray = ray;
    cub->north = north;
    cub->east = east;
    cub->south = south;
    cub->west = west;
    cub->sky = sky;
    cub->floor = floor;
    cub->move = move;
	cub->mdata->NO = NULL;
	cub->mdata->SO = NULL;
	cub->mdata->EA = NULL;
	cub->mdata->WE = NULL;
	cub->mdata->sky = NULL;
	cub->mdata->floor = NULL;
	cub->mdata->F = NULL;
	cub->mdata->C = NULL;
	cub->map = NULL;
	cub->move->front = 0;
	cub->move->back = 0;
	cub->move->right = 0;
	cub->move->left = 0;
	cub->move->front_a = 0;
	cub->move->back_a = 0;
	cub->move->right_a = 0;
	cub->move->left_a = 0;
	cub->move->angle_l = 0;
	cub->move->angle_r = 0;
	cub->fps = NULL;
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

void	ft_init_orientation(t_cub *cub)
{
	if (cub->player->direction == 'N')
		cub->player->orient = M_PI * 0.5;
	if (cub->player->direction == 'E')
		cub->player->orient = 0;
	if (cub->player->direction == 'S')
		cub->player->orient = - M_PI * 0.5;
	if (cub->player->direction == 'W')
		cub->player->orient = M_PI;
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
	cub->minimap = -1;
	cub->frames = 0;
	cub->start_time = ft_get_time();
    ft_print_view(cub);
    mlx_hook(cub->mlx->win, 17, 0, ft_exit, cub);
	mlx_hook(cub->mlx->win, 2, 0, key_hook_down, cub);
	mlx_hook(cub->mlx->win, 3, 0, key_hook_up, cub);
	mlx_loop_hook(cub->mlx->mlx, ft_move, cub);
    mlx_loop(cub->mlx->mlx);
}
