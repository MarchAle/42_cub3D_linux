/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/01 20:38:43 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "../mlx/mlx.h"
# include "../mlx_2/mlx2.h"
# include "../libft/libft.h"

# define STEP 0.05
# define ACCEL 25
# define O_ACC 20
# define MINIMAP_SIZE 300

# define FALSE 0
# define TRUE 1

# define MOVE 0
# define CAMERA 1

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

# define RIGHT 0
# define LEFT 1

# define TEX_WIDTH 248
# define TEX_HEIGHT 248

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     x[1];
    int     y[1];
}				t_img;

typedef struct  s_texture
{
    void    *img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
    int     x[1];
    int     y[1];
}	t_texture;

typedef struct s_mdata
{
    int		screen[2];
    char	*NO;
    char	*SO;
    char	*EA;
    char	*WE;
    char	*sky;
    char	*floor;
    char	**C;
    char	**F;
    int     c_color;
    int     f_color;
	int		max_size;
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
    float   texture_offset_x;
    float   texture_offset_y;
}   t_ray;

typedef struct s_player
{
    float   dist;
    char	direction;
    float   orient;
    float	x;
    float	y;
    float	map_x;
    float	map_y;
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

typedef struct s_move
{
    int     front;
    int     back;
    int     right;
    int     left;
    int     front_a;
    int     back_a;
    int     right_a;
    int     left_a;
    int     angle_r;
    int     angle_l;
    int		angle_r_a;
    int		angle_l_a;
}   t_move;

typedef struct s_cub
{
    struct s_img    	*img;
    struct s_texture    *north;
    struct s_texture    *east;
    struct s_texture    *south;
    struct s_texture    *west;
    struct s_texture    *sky;
    struct s_texture    *floor;
    struct s_mdata  	*mdata;
    struct s_player 	*player;
    struct s_ray    	*ray;
    struct s_mlx    	*mlx;
    struct s_move       *move;
    char            	**map;
    int             	minimap;
    int                	frames;
    char                *fps;
    long                start_time;
}   t_cub;

int     main(int ac, char **av);
void	ft_init_struct(t_cub *cub);
void	ft_init_texture(t_cub *cub);
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
float   ft_raycast(int i, t_cub *cub, int print_ray, int minimap_size);
void    ft_get_direction(t_cub *cub);
void    ft_mini_map(t_cub *cub);

int	    key_hook_down(int keycode, t_cub *cub);
int	    key_hook_up(int keycode, t_cub *cub);

int	    ft_move(t_cub *cub);
void	ft_move_front(t_cub *cub);
void	ft_move_back(t_cub *cub);
void	ft_move_right(t_cub *cub);
void	ft_move_left(t_cub *cub);
void	ft_move_camera(t_cub *cub, int dir);

void	ft_check_collision(t_cub *cub, float x, float y);

void	ft_offset_init(t_cub *cub);
float   ft_dist_to_wall(t_cub *cub);
void    ft_nearest_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_wall_y(t_cub *cub, float *shortest_dist);
void    ft_nearest_north_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_south_wall_x(t_cub *cub, float *shortest_dist);
void    ft_nearest_north_wall_y(t_cub *cub, float *shortest_dist);
void    ft_nearest_south_wall_y(t_cub *cub, float *shortest_dist);

long	ft_get_time(void);
int		ft_exit(t_cub *cub);

#endif