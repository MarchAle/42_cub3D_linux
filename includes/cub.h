/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:22:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/05/31 16:28:43 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

# define BORDER_ERR 0
# define FILE_ERR 1
# define INPUT_ERR 2

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


typedef struct s_cub
{
    struct s_mdata  *mdata;
    char            **map;
}   t_cub;

int     main(int ac, char **av);
void	ft_init_struct(t_cub *cub);
void	ft_parse_file(char *file, t_cub *cub);
void	ft_init_map(t_cub *cub, int fd);
void	ft_get_param(t_cub *cub, char **tmp_line);
void	ft_get_path_texture(char *texture, char **tmp_line);
void	ft_open_texture(char *dir);
void	ft_check_colors(t_cub *cub, char **tmp_line);
void	ft_get_colors(char **colors);

#endif