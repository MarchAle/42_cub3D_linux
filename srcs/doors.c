#include "../includes/cub.h"

float	ease_in_out_cubic(float t)
{
	if (t > 1)
		t = 1;
	else if (t < 0)
		t = 0;
	return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
}

void	ft_doors_detection(t_cub *cub)
{
	t_door *door = cub->doors;
    cub->player->door_open = 0;

	while (door)
	{
		// reset doors on map after monster passage
		if (cub->map[door->y][door->x] == '0')
		{
			cub->map[door->y][door->x] = 'D';
			door->animation = 1;
		}
		if (cub->player->x > door->x_min && cub->player->x < door->x_max && cub->player->y > door->y_min && cub->player->y < door->y_max && cub->player->keys)
		{
			if (door->animation < 1)
				door->opening = ease_in_out_cubic(door->animation);
			if (door->animation > 1)
				door->animation = 1;
			door->animation += OPEN_SPEED;
		}
		else
		{
			if (door->animation > 0)
				door->opening = ease_in_out_cubic(door->animation);
			if (door->animation < 0)
				door->animation = 0;
			door->animation -= OPEN_SPEED;
		}
        if (door->animation > 0.8)
            cub->player->door_open = 1;
		door = door->next;
	}
}
