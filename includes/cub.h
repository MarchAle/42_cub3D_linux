/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:18:22 by amarchal          #+#    #+#             */
/*   Updated: 2022/09/30 15:52:04 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define FOV 75

# define WIN_HEIGHT 900
# define WIN_RATIO 1.7777778	// 16/9
//# define WIN_RATIO 1.25			// 5/4

# define STEP 0.1
# define ACCEL 12
# define O_ACC 8
# define MINIMAP_SIZE 300
# define DOOR_DIST 1.5
# define OPEN_SPEED 0.05
# define MONSTER_STEP 0.05
# define HEALTH 150
# define NO_HIT_TIME 15
# define KICK 0.38

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
# define MALLOC 6
# define ORIENT 7
# define OPEN 8
# define EMPTY_LINE 9

# define NW 1
# define NE 2
# define SW 3
# define SE 4

# define N 1
# define E 2
# define S 3
# define W 4 

# define X 0
# define Y 1

# define RIGHT 0
# define LEFT 1

# define WALL -1
# define MONSTER 0
# define DOOR 1

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x[1];
	int		y[1];
}	t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width[1];
	int		height[1];
}	t_texture;

typedef struct s_mdata
{
	int		screen[2];
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*sky;
	char	*floor;
	char	*sprite;
	char	*flashlight;
	char	*door;
	char	**c;
	char	**f;
	int		c_color;
	int		f_color;
	int		max_size;
	int		start_build;
}	t_mdata;

typedef struct s_ray
{
	float			x;
	float			y;
	int				direction;
	float			wall_dist;
	float			wall_height;
	float			angle;
	float			angle_player;
	float			dist_to_x;
	float			dist_to_y;
	int				hit_wall;
	int				wall_orientation;
	float			texture_offset_x;
	float			texture_offset_y;
	struct s_sprite	*sprites;
}	t_ray;

typedef struct s_player
{
	float	dist;
	char	direction;
	float	orient;
	float	x;
	float	y;
	float	map_x;
	float	map_y;
	float	offset_x;
	float	offset_y;
	int		door_open;
	int 	health;
	int		last_hit;
	float	kick_x;
	float	kick_y;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width[1];
	int		height[1];
}	t_mlx;

typedef struct s_move
{
	int	front;
	int	back;
	int	right;
	int	left;
	int	front_a;
	int	back_a;
	int	right_a;
	int	left_a;
	int	angle_r;
	int	angle_l;
	int	angle_r_a;
	int	angle_l_a;
}	t_move;

typedef struct s_tex_color
{
	int	**north;
	int	**east;
	int	**south;
	int	**west;
	int	**sky;
	int	**floor;
}	t_tex_color;

typedef struct s_render_param
{
	int		y_offset_px;
	float	y_offset;
	float	floor_angle;
	float	floor_dist;
	float	pixel_x;
	float	pixel_y;
}	t_render_param;

typedef struct s_sprite
{
	int 			type;
	float 			x;
	float 			y;
	float			dist;
	float			height;
	float			x_offset;
	float			y_offset;
	int				to_display;
	float			adjacent;
	struct s_sprite	*next;
	struct s_sprite	*previous;
}	t_sprite;

typedef struct s_calc
{
	float	alpha;			// ft_angleClaculation()
	float	cosalpha;		// ft_angleClaculation()
	float	sinalpha;		// ft_angleClaculation()
	float	d;				// ft_angleClaculation()
	float	powd;			// ft_angleClaculation()
	float	fovHalf;		// ft_raycast()
	float	piHalf;
	float	cosAngle;
	float	sinAngle;
	float	tanAngle;
	float	half_width;
	float	half_height;
	float	max_vignet;		// 
}	t_calc;

typedef struct s_door
{
	int				id;
	int				x;
	float			x_min;
	float			x_max;
	int				y;
	float			y_min;
	float			y_max;
	int				near_player;
	float			animation;
	float			opening;
	struct s_door	*next;
}	t_door;

typedef struct s_monster
{
	int					id;
	float				x;
	float				y;
	int					follow;
	struct s_monster	*next;
}	t_monster;

typedef struct s_cub
{
	float					*angles;
	struct s_calc			*calc;
	struct s_img			*img;
	struct s_texture		*north;
	struct s_texture		*east;
	struct s_texture		*south;
	struct s_texture		*west;
	struct s_texture		*sky;
	struct s_texture		*floor;
	struct s_texture		*sprite;
	struct s_texture		*flashlight;
	struct s_texture		*door;
	struct s_render_param	*sky_p;
	struct s_render_param	*floor_p;
	struct s_tex_color		*tex_color;
	struct s_mdata			*mdata;
	struct s_player			*player;
	struct s_ray			*ray;
	struct s_mlx			*mlx;
	struct s_move			*move;
	struct s_door			*doors;
	struct s_monster		*monsters;
	char					**map;
	char					**monster_map;
	int						minimap;
	int						blur;
	int						light;
	float					step;
	int						frames;
	char					*fps;
	long					fps_time;
	long					frame_time;
}	t_cub;

void	ft_error(int type);

int		main(int ac, char **av);
void	ft_init_struct(t_cub *cub);
void    ft_init_calculs(t_cub *cub);
void	ft_init_texture(t_cub *cub);
void	ft_parse_file(char *file, t_cub *cub);
void	ft_get_lines(t_cub *cub, int fd);
void	ft_get_param(t_cub *cub, char **tmp_line);
void	ft_get_path_texture(char *texture, char **tmp_line);
void	ft_open_texture(char *dir);
int		ft_check_colors(t_cub *cub, char **tmp_line);
void	ft_get_colors(char **colors);
int		ft_all_params(t_cub *cub);
void	ft_build_map(t_cub *cub, char *line);
void	ft_init_monster_map(t_cub *cub);
void	ft_empty_line_checker(t_cub *cub, char *line);
void	ft_empty_file(char *line);
void	ft_check_extension(char *file, char *ext);

void	ft_mlx_init(t_cub *cub);
void	ft_print_img(t_cub *cub);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ft_multi_pixel_put(t_cub *cub, t_img *img, int x, int y, int downscaling, int color);
int		ft_downscaling(t_cub *cub, int i, int j);

void	ft_check_char(char c, int x, int y, t_cub *cub);
void	ft_check_border(char **map, int x, int y);
void	ft_check_line(char *line, int y, char **map, t_cub *cub);
int		ft_rgb_to_hex(char **rgb);
void	ft_convert_colors(t_cub *cub);
void	ft_parse_map(t_cub *cub);

void	ft_start_game(t_cub *cub);
void	ft_print_view(t_cub *cub);
float	ft_raycast(int i, t_cub *cub, int print_ray, int minimap_size);
void    ft_trigo_angle(t_cub *cub);
void	ft_get_direction(t_cub *cub);
void	ft_mini_map(t_cub *cub);

int		ft_rgb_to_hex(char **rgb);
void	ft_convert_colors(t_cub *cub);
int		ft_get_color_from_texture(t_texture *tex, int x, int y);
int		ft_get_color_from_img(t_img *img, int x, int y);
int 	ft_pix_color_calc(t_cub *cub, int j, t_texture *tex);
float	ft_flashlight(t_cub *cub, float dist, int i, int j, int wall);
int		ft_shade_color(int pix_color, float dist);
int		ft_fade_color(int pix_color, float dist);

void	ft_render_img(t_cub *cub, float dist, int i);
void	ft_render_wall(t_cub *cub, int i, int j, float dist);
void	ft_render_sky(t_cub *cub, int i, int j);
void	ft_render_floor(t_cub *cub, int i, int j, float dist);
void    ft_sprites_calc(t_cub *cub);
void	ft_render_sprites(t_cub *cub, int i, int j);
void	ft_fps(t_cub *cub);

int		key_hook_down(int keycode, t_cub *cub);
int		key_hook_up(int keycode, t_cub *cub);

int		ft_loop_move(t_cub *cub);
void	ft_move(t_cub *cub);
void	ft_move_front(t_cub *cub);
void	ft_move_back(t_cub *cub);
void	ft_move_right(t_cub *cub);
void	ft_move_left(t_cub *cub);
void	ft_move_camera(t_cub *cub, int dir);

void	ft_acceleration(int	*dir, int *accel, int type);

void	ft_check_collision(t_cub *cub, float x, float y);

void	ft_offset_init(t_cub *cub);
float	ft_dist_to_wall(t_cub *cub);
void	ft_nearest_wall_x(t_cub *cub, float *shortest_dist);
void	ft_nearest_wall_y(t_cub *cub, float *shortest_dist);
void	ft_nearest_north_wall_x(t_cub *cub, float *shortest_dist);
void	ft_nearest_south_wall_x(t_cub *cub, float *shortest_dist);
void	ft_nearest_north_wall_y(t_cub *cub, float *shortest_dist);
void	ft_nearest_south_wall_y(t_cub *cub, float *shortest_dist);
float	x_offset_calc(t_cub *cub, float dist, int axe, int type);

void	print_monster_map(t_cub *cub);
void    monster_detected(t_cub *cub, int x, int y);
// void    ft_move_monster(t_cub *cub);
void    *ft_move_monster(void *cub);

void	ft_doors_detection(t_cub *cub);

long	ft_get_time(void);
int		ft_exit(t_cub *cub);

t_sprite	*ft_lstnew_sprite(float x, float y, int type, float dist, float x_offset);
void		ft_lstadd_back_sprite(t_sprite **alst, t_sprite *new);
t_sprite	*ft_lstlast_sprite(t_sprite *lst);
void		ft_lstfree_sprite(t_sprite **lst);

t_door		*ft_lstnew_door(int x, int y);
void		ft_lstadd_back_door(t_door **alst, t_door *new);
t_door		*ft_lstlast_door(t_door *lst);
void		ft_lstfree_door(t_door **lst);

t_monster	*ft_lstnew_monster(float x, float y);
void		ft_lstadd_back_monster(t_monster **alst, t_monster *new);
t_monster	*ft_lstlast_monster(t_monster *lst);
void		ft_lstfree_monster(t_monster **lst);

#endif