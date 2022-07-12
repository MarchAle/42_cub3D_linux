/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:02:09 by amarchal          #+#    #+#             */
/*   Updated: 2022/07/12 11:19:32 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_check_extension(char *file, char *ext)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i--] != ext[2])
		ft_error(EXT_ERR);
	if (file[i--] != ext[1])
		ft_error(EXT_ERR);
	if (file[i--] != ext[0])
		ft_error(EXT_ERR);
	if (file[i--] != '.')
		ft_error(EXT_ERR);
}

void	ft_open_texture(char *dir)
{
	ft_check_extension(dir, "xpm");
	if (open(dir, O_RDONLY) == -1)
		ft_error(OPEN);
}

void	ft_fps(t_cub *cub)
{
	char	*frames;

	if (ft_get_time() - cub->fps_time > 1000)
	{
		if (cub->fps)
			free(cub->fps);
		frames = ft_itoa(cub->frames);
		if (!frames)
			ft_error(MALLOC);
		cub->fps = ft_strjoin("FPS : ", frames);
		free(frames);
		cub->frames = 0;
		cub->fps_time = ft_get_time();
	}
	if (cub->fps)
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			30, 30, 0x934d1d, cub->fps);
}

void	ft_empty_line_checker(t_cub *cub, char *line)
{
	static int	empty_line = 0;

	if (empty_line != 0 && line[0] != '\n')
		ft_error(EMPTY_LINE);
	if (line[0] != '\n' && cub->mdata->start_build == 0)
		cub->mdata->start_build = 1;
	if (cub->mdata->start_build == 1 && line[0] == '\n')
		empty_line = 1;
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
