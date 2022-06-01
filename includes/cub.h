/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/06/01 13:06:47 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

# define FILE_ERR 0
# define INPUT_ERR 1
# define BORDER_ERR 2
# define CHAR_ERR 3
# define PLAYER_ERR 4

typedef struct s_mdata
{
    int     screen[2];
    char    *NO;
    char    *SO;
    char    *EA;
    char    *WE;
    char    **F;
    char    **C;
}   t_mdata;

typedef struct s_player
{
    char    direction;
    int     x;
    int     y;
}   t_player;

typedef struct s_cub
{
    struct s_mdata  *mdata;
    struct s_player *player;
    char            **map;
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

void    ft_parse_error(int type);
void    ft_check_char(char c, int x, int y, t_cub *cub);
void    ft_check_border(char **map, int x, int y);
void    ft_check_line(char *line, int y, char **map, t_cub *cub);
void    ft_parse_map(t_cub *cub);

#endif