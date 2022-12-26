#include "../includes/cub.h"

// void    is_monster_shot(t_cub *cub, t_ray *ray, int j, int pix_color, t_sprite *sprite)
// {
//     static col_pix = 0;
//     static sum_color = 0;

// // check pour chaque colonne de pixel, si une couleur a été retournée et que player->shoot et que if (ray->angle_player > -0.0005 && ray->angle_player < 0.0005) alors retrouver le monstre correspondant, celui ci est touché
//     // if (j > WIN_HEIGHT - 5)
//     // {
//     //     if 
//     // }
// }

void    monster_position(t_cub *cub, t_ray *ray, int x, int y)
{

    pthread_mutex_lock(&cub->mutex);
    t_monster *monster = cub->monsters;

    while (monster)
    {
        // MANAGE SHOOT HERE
        if (ray->angle_player > -0.0005 && ray->angle_player < 0.0005)
            monster->shot = 1;
        if ((int)monster->x == x && (int)monster->y == y)
        {
            ft_lstadd_back_sprite(&ray->sprites, ft_lstnew_sprite(monster->x, monster->y, MONSTER, 0, 0));
        }
        monster = monster->next;
    }
    pthread_mutex_unlock(&cub->mutex);
}

void    monster_detected(t_cub *cub, t_ray *ray, int x, int y)
{
    int i = -1;
    int j;
    while (i <= 1)
    {
        j = -1;
        while (j <= 1)
        {
            monster_position(cub, ray, x + i, y + j);
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
    
	while (cub->map[i])
	{
		printf("%s", cub->map[i]);
		i++;
	}
}

void    ft_move_monster(t_cub *cub)
{
    t_monster   *monster = cub->monsters;

    while (monster)
    {
        float   old_x = monster->x;
        float   old_y = monster->y;

        float dist_to_player = sqrtf(powf(monster->x - cub->player->x, 2) + powf(monster->y - cub->player->y, 2));
        if (dist_to_player < 0.4 && cub->player->last_hit == 0)
        {
            cub->player->health -= 10;
            cub->player->last_hit = NO_HIT_TIME;
            cub->player->kick_x = (monster->x - cub->player->x) * KICK / (dist_to_player + 0.001);
            cub->player->kick_y = (monster->y - cub->player->y) * KICK / (dist_to_player + 0.001);
        }
        
        if (dist_to_player < 3)
            monster->follow = TRUE;
        else if (dist_to_player > 5)
            monster->follow = FALSE;
        
        if (monster->follow)
        {
            float factor = dist_to_player / MONSTER_STEP + 0.00001;
            float step_x = (monster->x - cub->player->x) / factor;
            float step_y = (monster->y - cub->player->y) / factor;
            if (cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == '0' || cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == 'X' || cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == 'K' || cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == 'P' || (cub->map[(int)(monster->y - step_y)][(int)(monster->x - step_x)] == 'D' && cub->player->door_open == 1)) 
            {
                ft_check_collision_monster(cub, monster, monster->x - step_x, monster->y - step_y);
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
        }
        monster = monster->next;
    }
    // print_map(cub);
}