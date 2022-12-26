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

float	dist_monster_to_monster(float monster_x, float monster_y, t_monster *other_monster)
{
	float dist = sqrtf(powf(monster_x - other_monster->x, 2) + powf(monster_y - other_monster->y, 2)); 
	return (dist);
}

void	ft_check_collision_monster(t_cub *cub, t_monster *monster, float x, float y)
{
	t_monster   *other_monster = cub->monsters;

    while (other_monster)
    {
		if ((dist_monster_to_monster(x, y, other_monster) < 0.2 && monster->id != other_monster->id) || dist_monster_to_monster(cub->player->x, cub->player->y, monster) < 0.2)
			return ;
		other_monster = other_monster->next;
	}
	if ((cub->map[(int)floor(monster->y)][(int)floor(x)] != '1' && cub->map[(int)floor(monster->y)][(int)floor(x)] != 'D') || (cub->map[(int)floor(monster->y)][(int)floor(x)] == 'D' && cub->player->door_open == 1))
		ft_move_x_monster(cub, monster, x);
	else
		ft_wall_gap_x_monster(monster, x);
	if ((cub->map[(int)floor(y)][(int)floor(monster->x)] != '1' && cub->map[(int)floor(y)][(int)floor(monster->x)] != 'D') || (cub->map[(int)floor(y)][(int)floor(monster->x)] == 'D' && cub->player->door_open == 1))
		ft_move_y_monster(cub, monster, y);
	else
		ft_wall_gap_y_monster(monster, y);
}
