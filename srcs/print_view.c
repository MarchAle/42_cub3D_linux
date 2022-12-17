#include "../includes/cub.h"

int		avgColorCalc(t_cub *cub, int x, int y, int blurIntensity)
{
	int avgred = 0;
	int avggreen = 0;
	int avgblue = 0;
	int i = x - blurIntensity;
	int div = 1;

	while (i < x + blurIntensity)
	{
		int j = y - blurIntensity;
		while (j < y + blurIntensity)
		{
			if ((i > 0 && i < cub->mdata->screen[0]) && (j > 0 && j < cub->mdata->screen[1]))
			{
				avgred += (ft_get_color_from_img(cub->img, i, j) & 0x00ff0000) >> 16;
				avggreen += (ft_get_color_from_img(cub->img, i, j) & 0x0000ff00) >> 8;
				avgblue += (ft_get_color_from_img(cub->img, i, j) & 0x000000ff);
				div++;
			}
			j += 2;
		}
		i += 2;
	}
	return ((((avgred / div) & 0xff) << 16) + (((avggreen / div) & 0xff) << 8) + ((avgblue / div) & 0xff));
}


void	ft_blur(t_cub *cub, int blurIntensity) //
{
	t_img	*blur_img;
	int i = 1;
	int j;
	int avgColor = 0;
	int downscaling = 4;

	blur_img = malloc(sizeof(t_img));
	if (!blur_img)
		ft_error(MALLOC);
	blur_img->img = mlx_new_image(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
	blur_img->addr = mlx_get_data_addr(blur_img->img, &blur_img->bits_per_pixel, &blur_img->line_length, &cub->img->endian);

	while (i < cub->mdata->screen[0])
	{
		j = 1;
		while (j < cub->mdata->screen[1])
		{
			avgColor = avgColorCalc(cub, i, j, blurIntensity);
			ft_multi_pixel_put(cub, blur_img, i, j, downscaling, avgColor);
			j += downscaling;
		}
		i += downscaling;
	}
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, blur_img->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, blur_img->img);
}

void    ft_health_bar(t_cub *cub)
{
    int offset_x = 60;
    int offset_y = WIN_HEIGHT - 0.08 * WIN_HEIGHT;
    int x = 0;
    int y;
    while (x < 120)
    {
        y = 0;
        while (y < 20)
        {
            if (x < 3 || x >= 117 || y < 3 || y >= 17)
                my_mlx_pixel_put(cub->img, x + offset_x, y + offset_y, 0x4F4444);
            else if (x < 118 * cub->player->health / HEALTH && cub->player->last_hit % 3 == 0)
                my_mlx_pixel_put(cub->img, x + offset_x, y + offset_y, 0x88E1212);
            y++;
        }
        x++;
    }
}

void	*routine_one(void *data)
{
	t_thread *thread = data;
	// int i = thread->cub->calc->half_width;
	int i = thread->cub->mdata->screen[0] * 0.35; //

	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	thread->cub->thread_one->ray = ray;
	t_render_param	*floor_p = malloc(sizeof(t_render_param));
	thread->cub->thread_one->ray->floor_p = floor_p;
	while (i > 0)
	{
		thread->ray->wall_dist = ft_raycast(i, thread->cub, thread->ray, FALSE, 0);
	
		ft_render_img(thread->cub, thread->ray, thread->cub->mdata->screen[0] - i);
		// if (thread->ray->sprites)
		// {
		// 	ft_lstfree_sprite(thread->ray->sprites);
		// 	thread->ray->sprites = NULL;
		// }
		if (i < thread->cub->mdata->screen[0] * 0.10 || i > thread->cub->mdata->screen[0] * 0.90)
			i -= 5;
		else if (i < thread->cub->mdata->screen[0] * 0.15 || i > thread->cub->mdata->screen[0] * 0.85)
			i -= 4;
		else if (i < thread->cub->mdata->screen[0] * 0.25 || i > thread->cub->mdata->screen[0] * 0.75)
			i -= 3;
		else if (i < thread->cub->mdata->screen[0] * 0.40 || i > thread->cub->mdata->screen[0] * 0.60)
			i -= 2;
		else
			i--;
	}
	return NULL;
}

void	*routine_two(void *data)
{
	t_thread *thread = data;
	int i = thread->cub->mdata->screen[0] * 0.5;

	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	thread->cub->thread_two->ray = ray;
	t_render_param	*floor_p = malloc(sizeof(t_render_param));
	thread->cub->thread_two->ray->floor_p = floor_p;
	while (i > thread->cub->mdata->screen[0] * 0.35) //
	{
		thread->ray->wall_dist = ft_raycast(i, thread->cub, thread->ray, FALSE, 0);
		ft_render_img(thread->cub, thread->ray, thread->cub->mdata->screen[0] - i);
		// if (thread->ray->sprites)
		// {
		// 	ft_lstfree_sprite(thread->ray->sprites);
		// 	thread->ray->sprites = NULL;
		// }
		if (i < thread->cub->mdata->screen[0] * 0.10 || i > thread->cub->mdata->screen[0] * 0.90)
			i -= 5;
		else if (i < thread->cub->mdata->screen[0] * 0.15 || i > thread->cub->mdata->screen[0] * 0.85)
			i -= 4;
		else if (i < thread->cub->mdata->screen[0] * 0.25 || i > thread->cub->mdata->screen[0] * 0.75)
			i -= 3;
		else if (i < thread->cub->mdata->screen[0] * 0.40 || i > thread->cub->mdata->screen[0] * 0.60)
			i -= 2;
		else
			i--;
	}
	return NULL;
}

void	*routine_three(void *data)
{
	t_thread *thread = data;
	int i = thread->cub->mdata->screen[0] * 0.65;

	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	thread->cub->thread_three->ray = ray;
	t_render_param	*floor_p = malloc(sizeof(t_render_param));
	thread->cub->thread_three->ray->floor_p = floor_p;
	while (i > thread->cub->mdata->screen[0] * 0.5)
	{
		thread->ray->wall_dist = ft_raycast(i, thread->cub, thread->ray, FALSE, 0);
		ft_render_img(thread->cub, thread->ray, thread->cub->mdata->screen[0] - i);
		// if (thread->ray->sprites)
		// {
		// 	ft_lstfree_sprite(thread->ray->sprites);
		// 	thread->ray->sprites = NULL;
		// }
		if (i < thread->cub->mdata->screen[0] * 0.10 || i > thread->cub->mdata->screen[0] * 0.90)
			i -= 5;
		else if (i < thread->cub->mdata->screen[0] * 0.15 || i > thread->cub->mdata->screen[0] * 0.85)
			i -= 4;
		else if (i < thread->cub->mdata->screen[0] * 0.25 || i > thread->cub->mdata->screen[0] * 0.75)
			i -= 3;
		else if (i < thread->cub->mdata->screen[0] * 0.40 || i > thread->cub->mdata->screen[0] * 0.60)
			i -= 2;
		else
			i--;
	}
	return NULL;
}

void	*routine_four(void *data)
{
	t_thread *thread = data;
	int i = thread->cub->mdata->screen[0];

	t_ray *ray = malloc(sizeof(t_ray));
	thread->cub->thread_four->ray = ray;
	t_render_param	*floor_p = malloc(sizeof(t_render_param));
	thread->cub->thread_four->ray->floor_p = floor_p;
	while (i > thread->cub->mdata->screen[0] * 0.65)
	{
		thread->ray->wall_dist = ft_raycast(i, thread->cub, thread->ray, FALSE, 0);
		ft_render_img(thread->cub, thread->ray, thread->cub->mdata->screen[0] - i);
		// if (thread->ray->sprites)
		// {
		// 	ft_lstfree_sprite(thread->ray->sprites);
		// 	thread->ray->sprites = NULL;
		// }
		if (i < thread->cub->mdata->screen[0] * 0.10 || i > thread->cub->mdata->screen[0] * 0.90)
			i -= 5;
		else if (i < thread->cub->mdata->screen[0] * 0.15 || i > thread->cub->mdata->screen[0] * 0.85)
			i -= 4;
		else if (i < thread->cub->mdata->screen[0] * 0.25 || i > thread->cub->mdata->screen[0] * 0.75)
			i -= 3;
		else if (i < thread->cub->mdata->screen[0] * 0.40 || i > thread->cub->mdata->screen[0] * 0.60)
			i -= 2;
		else
			i--;
	}
	return NULL;
}


void	ft_print_view(t_cub *cub)
{
	// int		i;
	t_img	*img;


	
	img = malloc(sizeof(t_img));
	if (!img)
		ft_error(MALLOC);
	cub->img = img;
	cub->img->img = mlx_new_image(cub->mlx->mlx, cub->mdata->screen[0], cub->mdata->screen[1]);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel, &cub->img->line_length, &cub->img->endian);
	cub->img->bpp_divided = cub->img->bits_per_pixel / 8;
	// i = cub->mdata->screen[0];
	
	pthread_create(&cub->thread_one->thread, NULL, routine_one, cub->thread_one);
	pthread_create(&cub->thread_two->thread, NULL, routine_two, cub->thread_two);
	pthread_create(&cub->thread_three->thread, NULL, routine_three, cub->thread_three);
	pthread_create(&cub->thread_four->thread, NULL, routine_four, cub->thread_four);
	pthread_join(cub->thread_four->thread, NULL);
	pthread_join(cub->thread_three->thread, NULL);
	pthread_join(cub->thread_two->thread, NULL);
	pthread_join(cub->thread_one->thread, NULL);
	// while (i > 0)
	// {
	// 	cub->thread_one->i = i;
	// 	pthread_create(&cub->thread_one->thread, NULL, routine_one, cub->thread_one);
		
	// 	// routine(cub->thread_one);
	// 	// cub->ray->wall_dist = ft_raycast(i, cub, cub->ray, FALSE, 0);
	// 	// ft_render_img(cub, cub->ray->wall_dist, cub->mdata->screen[0] - i);
	// 	// ft_lstfree_sprite(&cub->ray->sprites);
	// 	if (cub->blur == TRUE)
	// 		i -= 2;
	// 	else
	// 	{
	// 		if (i < cub->mdata->screen[0] * 0.10 || i > cub->mdata->screen[0] * 0.90)
	// 			i -= 5;
	// 		else if (i < cub->mdata->screen[0] * 0.15 || i > cub->mdata->screen[0] * 0.85)
	// 			i -= 4;
	// 		else if (i < cub->mdata->screen[0] * 0.25 || i > cub->mdata->screen[0] * 0.75)
	// 			i -= 3;
	// 		else if (i < cub->mdata->screen[0] * 0.40 || i > cub->mdata->screen[0] * 0.60)
	// 			i -= 2;
	// 		else
	// 			i--;
	// 	}
	// 	// if (i > 0)
	// 	// {
	// 	// 	cub->thread_two->i = i;
	// 	// 	pthread_create(&cub->thread_two->thread, NULL, routine, cub->thread_two);

	// 	// }
	// 	// if (cub->blur == TRUE)
	// 	// 	i -= 2;
	// 	// else
	// 	// {
	// 	// 	if (i < cub->mdata->screen[0] * 0.10 || i > cub->mdata->screen[0] * 0.90)
	// 	// 		i -= 5;
	// 	// 	else if (i < cub->mdata->screen[0] * 0.15 || i > cub->mdata->screen[0] * 0.85)
	// 	// 		i -= 4;
	// 	// 	else if (i < cub->mdata->screen[0] * 0.25 || i > cub->mdata->screen[0] * 0.75)
	// 	// 		i -= 3;
	// 	// 	else if (i < cub->mdata->screen[0] * 0.40 || i > cub->mdata->screen[0] * 0.60)
	// 	// 		i -= 2;
		// 	else
	// 	// 		i--;
	// 	// }
	// 	// pthread_join(cub->thread_two->thread, NULL);
	// 	pthread_join(cub->thread_one->thread, NULL);
	// }
    ft_health_bar(cub);
	if (cub->minimap == TRUE)
		ft_mini_map(cub);
	if (cub->blur == TRUE)
	{
		// pthread_t 	thread = 0;
		// pthread_create(&thread, NULL, ft_blur, &cub);
		// pthread_join(thread, NULL);
		ft_blur(cub, 7);
	}
	else
		mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->img->img, 0, 0);
	// mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->flashlight->img, cub->mdata->screen[0] - cub->flashlight->width[0], cub->mdata->screen[1] - cub->flashlight->height[0]);
	mlx_destroy_image(cub->mlx->mlx, cub->img->img);
	free(img);
	cub->frames++;
}