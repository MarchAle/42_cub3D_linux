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

void	ft_multi_pixel_put(t_cub *cub, t_img *img, int x, int y, int downscaling, int color)
{
	int i = 0;
	while (i < downscaling && x + i < cub->mdata->screen[0])
	{
		int j = 0;
		while (j < downscaling)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int		ft_downscaling(t_cub *cub, int i, int j)
{
	int result = 1;

	if (i < cub->mdata->screen[0] * 0.10 || i > cub->mdata->screen[0] * 0.90)
		result++;
	if (i < cub->mdata->screen[0] * 0.15 || i > cub->mdata->screen[0] * 0.85)
		result++;
	if (i < cub->mdata->screen[0] * 0.25 || i > cub->mdata->screen[0] * 0.75)
		result++;
	if (i < cub->mdata->screen[0] * 0.40 || i > cub->mdata->screen[0] * 0.60)
		result++;
	if (j < cub->mdata->screen[1] * 0.10 || j > cub->mdata->screen[1] * 0.90)
		result++;
	if (j < cub->mdata->screen[1] * 0.15 || j > cub->mdata->screen[1] * 0.85)
		result++;
	if (j < cub->mdata->screen[1] * 0.25 || j > cub->mdata->screen[1] * 0.70)
		result++;
	if (j < cub->mdata->screen[1] * 0.40 || j > cub->mdata->screen[1] * 0.60)
		result++;
	(void)i;
	(void)j;
	(void)cub;
	return (result);
}