#include "../includes/cub.h"

void	ft_move_x_monster(t_cub *cub, t_monster *monster, float x)
{
	if (x - (int)floor(x) >= (1 - STEP)
		&& (cub->map[(int)floor(monster->y)][(int)floor(x) + 1] == '1' || (cub->map[(int)floor(monster->y)][(int)floor(x) + 1] == 'D' && cub->player->door_open == 0)))
		monster->x = (int)floor(monster->x) + (1 - STEP);
	else if (x - (int)floor(x) <= STEP
		&& (cub->map[(int)floor(monster->y)][(int)floor(x) - 1] == '1' || (cub->map[(int)floor(monster->y)][(int)floor(x) - 1] == 'D' && cub->player->door_open == 0)))
		monster->x = (int)floor(monster->x) + STEP;
	else
		monster->x = x;
}

void	ft_wall_gap_x_monster(t_monster *monster, float x)
{
	if ((int)floor(x) > (int)floor(monster->x))
	{
		if ((int)floor(monster->x) + (1 - STEP) < monster->x)
			monster->x = (int)floor(monster->x) + (1 - STEP);
	}
	else if ((int)floor(x) < (int)floor(monster->x))
	{
		if ((int)floor(monster->x) + STEP > monster->x)
			monster->x = (int)floor(monster->x) + STEP;
	}
	else
		monster->x = x;
}

void	ft_move_y_monster(t_cub *cub, t_monster *monster, float y)
{
	if (y - (int)floor(y) >= (1 - STEP)
		&& (cub->map[(int)floor(y) + 1][(int)floor(monster->x)] == '1' || (cub->map[(int)floor(y) + 1][(int)floor(monster->x)] == 'D' && cub->player->door_open == 0)))
		monster->y = (int)floor(monster->y) + (1 - STEP);
	else if (y - (int)floor(y) <= STEP
		&& (cub->map[(int)floor(y) - 1][(int)floor(monster->x)] == '1' || (cub->map[(int)floor(y) - 1][(int)floor(monster->x)] == 'D' && cub->player->door_open == 0)))
		monster->y = (int)floor(monster->y) + STEP;
	else
		monster->y = y;
}

void	ft_wall_gap_y_monster(t_monster *monster, float y)
{
	if ((int)floor(y) > (int)floor(monster->y))
	{
		if ((int)floor(monster->y) + (1 - STEP) < monster->y)
			monster->y = (int)floor(monster->y) + (1 - STEP);
	}
	else if ((int)floor(y) < (int)floor(monster->y))
	{
		if ((int)floor(monster->y) + STEP > monster->y)
			monster->y = (int)floor(monster->y) + STEP;
	}
	else
		monster->y = y;
}

void	ft_check_collision_monster(t_cub *cub, t_monster *monster, float x, float y)
{
	if ((cub->map[(int)floor(monster->y)][(int)floor(x)] != '1' && cub->map[(int)floor(monster->y)][(int)floor(x)] != 'D') || (cub->map[(int)floor(monster->y)][(int)floor(x)] == 'D' && cub->player->door_open == 1))
		ft_move_x_monster(cub, monster, x);
	else
		ft_wall_gap_x_monster(monster, x);
	if ((cub->map[(int)floor(y)][(int)floor(monster->x)] != '1' && cub->map[(int)floor(y)][(int)floor(monster->x)] != 'D') || (cub->map[(int)floor(y)][(int)floor(monster->x)] == 'D' && cub->player->door_open == 1))
		ft_move_y_monster(cub, monster, y);
	else
		ft_wall_gap_y_monster(monster, y);
}
