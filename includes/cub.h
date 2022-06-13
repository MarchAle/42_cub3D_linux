/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/13 14:43:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../mlx_2/mlx2.h"
# include "../libft/libft.h"

# define FALSE 0
# define TRUE 1

# define FILE_ERR 0
# define INPUT_ERR 1
# define EXT_ERR 2
# define BORDER_ERR 3
# define CHAR_ERR 4
# define PLAYER_ERR 5
# define INPUT_ERR_TEST 6

# define NW 1
# define NE 2
# define SW 3
# define SE 4

# define N 1
# define E 2
# define S 3
# define W 4

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mdata
{
    int		screen[2];
    char	*NO;
    char	*SO;
    char	*EA;
    char	*WE;
    char	**C;
    char	**F;
    int     c_color;
    int     f_color;
}   t_mdata;

typedef struct s_ray
{
    /////
    float   x;
    float   y;
    /////
    int     direction;
    float   wall_height;
    float   angle;
    float	dist_to_x;
    float	dist_to_y;
    int     hit_wall;
    int     wall_orientation;
}   t_ray;

typedef struct s_player
{
    float   dist;
    char	direction;
    float   orientation;
    float	x;
    float	y;
    float	offset_x;
    float	offset_y;
}   t_player;

typedef struct s_mlx
{
    void	*mlx;
	void	*win;
	int		width[1];
	int		height[1];
}   t_mlx;

typedef struct s_cub
{
    /////
    struct s_img    *img;
    /////
    struct s_mdata  *mdata;
    struct s_player *player;
    struct s_ray    *ray;
    struct s_mlx    *mlx;
    char            **map;
    int             minimap;
}   t_cub;

int     main(int ac, char **av);
void	ft_init_struct(t_cub *cub);
void	ft_parse_file(char *file, t_cub *cub);
void	ft_get_lines(t_cub *cub, int fd);
void	ft_get_param(t_cub *cub, char **tmp_line);
void	ft_get_path_texture(char *texture, char **tmp_line);
void	ft_open_texture(char *dir);
void	ft_check_colors(t_cub *cub, char **tmp_line);
void	ft_get_colors(char **colors);
int     ft_all_params(t_cub *cub);
void	ft_build_map(t_cub *cub, char *line);
void	ft_empty_file(char *line);
void	ft_check_extension(char *map_cub);

void    ft_mlx_init(t_cub *cub);
void    ft_print_img(t_cub *cub);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    ft_draw_wall(t_cub *cub, float dist, int i);

void    ft_parse_error(int type);
void    ft_check_char(char c, int x, int y, t_cub *cub);
void    ft_check_border(char **map, int x, int y);
void    ft_check_line(char *line, int y, char **map, t_cub *cub);
int		ft_rgb_to_hex(char **rgb);
void	ft_convert_colors(t_cub *cub);
void    ft_parse_map(t_cub *cub);

void    ft_start_game(t_cub *cub);
void    ft_print_view(t_cub *cub);
float   ft_raycast(int i, t_cub *cub, int print_ray);
void    ft_get_direction(t_cub *cub);
void    ft_mini_map(t_cub *cub);
int		key_hook(int keycode, t_cub *cub);

float   ft_dist_to_wall(t_cub *cub);
void    ft_nearest_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_wall_y(t_cub *cub, float *shortest_dist);
void    ft_nearest_north_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_south_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_north_wall_y(t_cub *cub, float *shortest_dist);
void    ft_nearest_south_wall_y(t_cub *cub, float *shortest_dist);


int		ft_exit(t_cub *cub);

#endif