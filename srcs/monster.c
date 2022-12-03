#include "../includes/cub.h"

void    monster_position(t_cub *cub, int x, int y)
{
    t_monster *monster = cub->monsters;

    while (monster)
    {
        if ((int)monster->x == x && (int)monster->y == y)
            ft_lstadd_back_sprite(&cub->ray->sprites, ft_lstnew_sprite(monster->x, monster->y, MONSTER, 0, 0));
        monster = monster->next;
    }
}

void    monster_detected(t_cub *cub, int x, int y)
{
    int i = -1;
    int j;
    while (i <= 1)
    {
        j = -1;
        while (j <= 1)
        {
            monster_position(cub, x + i, y + j);
            j++;
        }
        i++;
    }
}

void    ft_free_monster_map(t_cub *cub)
{
    int i = 0;
    while (cub->monster_map[i])
    {
        free(cub->monster_map[i]);
        i++;
    }
    free(cub->monster_map);
}


void	print_map(t_cub *cub)
{
	int i = 0;
	// int j;
	while (cub->map[i])
	{
			printf("%s", cub->map[i]);
		// j = 0;
		// while (cub->map[i][j])
		// {
		// 	write(2, &cub->map[i][j], 1);
		// 	j++;
		// }
		i++;
	}
}

// void    ft_move_monster(t_cub *cub)
void    *ft_move_monster(void *data)
{
    t_cub       *cub = data;
    t_monster   *monster = cub->monsters;
    while (monster)
    {
        float   old_x = monster->x;
        float   old_y = monster->y;

        float dist_to_player = sqrtf(powf(monster->x - cub->player->x, 2) + powf(monster->y - cub->player->y, 2));
        float factor = dist_to_player / MONSTER_STEP;
        float step_x = (monster->x - cub->player->x) / factor;
        float step_y = (monster->y - cub->player->y) / factor;
        if (cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == '0' || cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == 'X')
        {
            monster->x -= step_x;
            monster->y -= step_y;
            if ((int)old_x != (int)monster->x)
            {
                cub->map[(int)monster->y][(int)old_x] = '0';
                cub->map[(int)monster->y][(int)monster->x] = 'X';
                ft_free_monster_map(cub);
                ft_init_monster_map(cub);
            }
            if ((int)old_y != (int)monster->y)
            {
                cub->map[(int)old_y][(int)monster->x] = '0';
                cub->map[(int)monster->y][(int)monster->x] = 'X';
                ft_free_monster_map(cub);
                ft_init_monster_map(cub);
            }
        }
        monster = monster->next;
    }
    return (0);
}