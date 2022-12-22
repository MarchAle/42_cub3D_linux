/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:45:41 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/12 11:10:25 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_struct_move(t_cub *cub)
{
	t_move		*move;

	move = malloc(sizeof(t_move));
	if (!move)
		ft_error(MALLOC);
	cub->move = move;
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
}

void	ft_init_struct_param(t_cub *cub)
{
	t_player		*player;
	t_thread		*thread_one;
	t_thread		*thread_two;
	t_thread		*thread_three;
	t_thread		*thread_four;
	t_render_param	*sky_p;
	// t_render_param	*floor_p;

	player = malloc(sizeof(t_player));
	thread_one = malloc(sizeof(t_thread));
	thread_two = malloc(sizeof(t_thread));
	thread_three = malloc(sizeof(t_thread));
	thread_four = malloc(sizeof(t_thread));
	sky_p = malloc(sizeof(t_render_param));
	// floor_p = malloc(sizeof(t_render_param));
	if (!player || !thread_one || !thread_two|| !thread_three || !thread_four || !sky_p/* || !floor_p*/)
		ft_error(MALLOC);
	cub->player = player;
	cub->sky_p = sky_p;
	// cub->floor_p = floor_p;
	thread_one->thread = 0;
	thread_two->thread = 0;
	thread_three->thread = 0;
	thread_four->thread = 0;
	thread_one->cub = cub;
	thread_two->cub = cub;
	thread_three->cub = cub;
	thread_four->cub = cub;
	cub->thread_one = thread_one;
	cub->thread_two = thread_two;
	cub->thread_three= thread_three;
	cub->thread_four = thread_four;
	if (pthread_mutex_init(&cub->mutex, NULL))
		ft_error(MALLOC); //// type d'erreur a changer
}

void	ft_init_struct_wall(t_cub *cub)
{
	t_texture	*north;
	t_texture	*east;
	t_texture	*south;
	t_texture	*west;

	north = malloc(sizeof(t_texture));
	east = malloc(sizeof(t_texture));
	south = malloc(sizeof(t_texture));
	west = malloc(sizeof(t_texture));
	if (!north || !east || !south || !west)
		ft_error(MALLOC);
	cub->north = north;
	cub->east = east;
	cub->south = south;
	cub->west = west;
}

void	ft_init_struct_floor_sky(t_cub *cub)
{
	t_texture	*sky;
	t_texture	*floor;
	t_texture	*sprite;
	t_texture	*flashlight;
	t_texture	*door;
	t_texture	*key;

	sky = malloc(sizeof(t_texture));
	floor = malloc(sizeof(t_texture));
	sprite = malloc(sizeof(t_texture));
	flashlight = malloc(sizeof(t_texture));
	door = malloc(sizeof(t_texture));
	key = malloc(sizeof(t_texture));
	if (!sky || !floor || !sprite || !flashlight || !door || !key)
		ft_error(MALLOC);
	cub->sky = sky;
	cub->floor = floor;
	cub->sprite = sprite;
	cub->flashlight = flashlight;
	cub->door = door;
	cub->key = key;
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata		*mdata;
	t_mlx		*mlx;
	t_calc		*calc;

	mdata = malloc(sizeof(t_mdata));
	mlx = malloc(sizeof(t_mlx));
	calc = malloc(sizeof(t_calc));
	if (!mdata || !mlx || !calc)
		ft_error(MALLOC);
	cub->mdata = mdata;
	cub->mlx = mlx;
	cub->calc = calc;
	cub->mdata->no = NULL;
	cub->mdata->so = NULL;
	cub->mdata->ea = NULL;
	cub->mdata->we = NULL;
	cub->mdata->sky = NULL;
	cub->mdata->floor = NULL;
	cub->mdata->sprite = NULL;
	cub->mdata->door = NULL;
	cub->mdata->key = NULL;
	cub->mdata->f = NULL;
	cub->mdata->c = NULL;
	cub->mdata->start_build = 0;
	cub->map = NULL;
	cub->fps = NULL;
	ft_init_struct_move(cub);
	ft_init_struct_param(cub);
	ft_init_struct_wall(cub);
	ft_init_struct_floor_sky(cub);
}
