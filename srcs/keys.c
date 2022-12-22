#include "../includes/cub.h"

void	ft_keys_detection(t_cub *cub)
{
	t_key *key = cub->keys;

	while (key)
	{
		// reset keys on map after monster passage
		if (cub->map[key->y][key->x] == '0' && key->taken == 0)
		{
			cub->map[key->y][key->x] = 'K';
		}
        if (key->x == (int)cub->player->x && key->y == (int)cub->player->y)
        {
            cub->map[key->y][key->x] = '0';
            key->taken = 1;
            cub->player->keys++;
        }
		key = key->next;
	}

    if (cub->key_anim_status == 0)
    {
        if (cub->key_anim < 1)
            cub->key_vertical = ease_in_out_cubic(cub->key_anim);
        cub->key_anim += BOUNCE_SPEED;
        if (cub->key_anim >= 1)
        {
            cub->key_anim = 1;
            cub->key_anim_status = 1;
        }
    }
    else
    {
        if (cub->key_anim > 0)
            cub->key_vertical = ease_in_out_cubic(cub->key_anim);
        cub->key_anim -= BOUNCE_SPEED;
        if (cub->key_anim <= 0)
        {
            cub->key_anim = 0;
            cub->key_anim_status = 0;
        }
    }
}
