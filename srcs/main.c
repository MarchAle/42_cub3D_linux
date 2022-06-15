/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/15 18:45:46 by amarchal         ###   ########.fr       */
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
	ft_init_texture(cub);
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
    
    mdata = malloc(sizeof(t_mdata));
    player = malloc(sizeof(t_player));
    mlx = malloc(sizeof(t_mlx));
	ray = malloc(sizeof(t_ray));
	north = malloc(sizeof(t_texture));
    if (!mdata || !player || !mlx || !ray || !north)
		exit(EXIT_FAILURE);
    cub->mdata = mdata;
    cub->player = player;
	cub->mlx = mlx;
    cub->ray = ray;
    cub->north = north;
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

void	ft_init_orientation(t_cub *cub)
{
	if (cub->player->direction == 'N')
		cub->player->orientation = M_PI * 0.5;
	if (cub->player->direction == 'E')
		cub->player->orientation = 0;
	if (cub->player->direction == 'S')
		cub->player->orientation = - M_PI * 0.5;
	if (cub->player->direction == 'W')
		cub->player->orientation = M_PI;
}

void    ft_start_game(t_cub *cub)
{
	ft_init_orientation(cub);
    ft_mlx_init(cub);
	cub->minimap = -1;
    ft_print_view(cub);
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	mlx_hook(cub->mlx->win, 17, 0, ft_exit, cub);
	mlx_hook(cub->mlx->win, 2, 0, key_hook, cub);
    mlx_loop(cub->mlx->mlx);
}
