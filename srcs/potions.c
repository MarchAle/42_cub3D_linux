#include "../includes/cub.h"

void	ft_potions_detection(t_cub *cub)
{
	t_potion *potion = cub->potions;

	while (potion)
	{
		// reset potions on map after monster passage
		if (cub->map[potion->y][potion->x] == '0' && potion->taken == 0)
		{
			cub->map[potion->y][potion->x] = 'P';
		}
        if (potion->x == (int)cub->player->x && potion->y == (int)cub->player->y && potion->taken == 0)
        {
            cub->map[potion->y][potion->x] = '0';
            potion->taken = 1;
            cub->player->health += 20;
        }
		potion = potion->next;
	}
}
