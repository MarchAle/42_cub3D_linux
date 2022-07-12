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
	t_ray			*ray;
	t_render_param	*sky_p;
	t_render_param	*floor_p;

	player = malloc(sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	sky_p = malloc(sizeof(t_render_param));
	floor_p = malloc(sizeof(t_render_param));
	if (!player || !ray || !sky_p || !floor_p)
		ft_error(MALLOC);
	cub->player = player;
	cub->ray = ray;
	cub->sky_p = sky_p;
	cub->floor_p = floor_p;
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

	sky = malloc(sizeof(t_texture));
	floor = malloc(sizeof(t_texture));
	if (!sky || !floor)
		ft_error(MALLOC);
	cub->sky = sky;
	cub->floor = floor;
}

void	ft_init_struct(t_cub *cub)
{
	t_mdata		*mdata;
	t_mlx		*mlx;

	mdata = malloc(sizeof(t_mdata));
	mlx = malloc(sizeof(t_mlx));
	if (!mdata || !mlx)
		ft_error(MALLOC);
	cub->mdata = mdata;
	cub->mlx = mlx;
	cub->mdata->no = NULL;
	cub->mdata->so = NULL;
	cub->mdata->ea = NULL;
	cub->mdata->we = NULL;
	cub->mdata->sky = NULL;
	cub->mdata->floor = NULL;
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
