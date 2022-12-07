#include "../includes/cub.h"

void    ft_sprites_calc(t_cub *cub)
{
    t_sprite *sprite = cub->ray->sprites;
    while (sprite)
    {
        sprite->to_display = TRUE;
        if (sprite->type == MONSTER)
        {
            float x =  sprite->x - cub->player->x;
            float y =  sprite->y - cub->player->y;

            float nx = x * cos(cub->player->orient) - y * sin(cub->player->orient);
            float ny = x * sin(cub->player->orient) + y * cos(cub->player->orient);

            float ray_sprite_offset = (ny - (tan(cub->ray->angle_player) * nx))* -1 + 0.5;

            sprite->x_offset = ray_sprite_offset;
            sprite->height = 1 / nx * cub->mdata->screen[1];
            sprite->dist = nx;
        }
        if (sprite->type == DOOR)
        {
            sprite->height = (1 / (sprite->dist * cos(cub->player->orient - cub->ray->angle))) * cub->mdata->screen[1];

            t_door *door = cub->doors;

            while (door)
            {
                if (sprite->x == door->x && sprite->y == door->y)
                    sprite->x_offset += door->opening;
                if (sprite->x_offset < 0)
                    sprite->to_display = FALSE;
                door = door->next;
            }
        }

        sprite = sprite->next;
    }
}

int ft_pix_color_calc_sprite(t_cub *cub, t_sprite *sprite, int j, t_texture *tex)
{
	int	color = 0;

    if (sprite->to_display == TRUE)
    {
        float sprite_offset_y = (float)((j - ((cub->mdata->screen[1] - sprite->height) / 2)) / (sprite->height) * tex->height[0]);
        color = ft_get_color_from_texture(tex, (int)(sprite->x_offset * tex->width[0]),	(int)sprite_offset_y);
    }
	return (color);
}

void    sort_sprites(t_cub *cub)
{
    int         sorted;
    t_sprite    *sprite = NULL;
    t_sprite    *tmp = NULL;
    t_sprite    *current = NULL;

    do
    {
        sorted = 0;
        sprite = cub->ray->sprites;
        while (sprite)
        {
            current = sprite;
            if (current->next && current->next->dist < current->dist)
            {
                // if (current->previous)
                //     current->previous->next = current->next;
                // else
                //     cub->ray->currents = current->next;

                tmp = current->next;
                current->next = tmp->next;
				tmp->next = current;
                // current = tmp;
                sorted = 1;
            }
            sprite = sprite->next;
        }
    } while (sorted == 0);
}

void    ft_render_sprites(t_cub *cub, int i, int j)
{
    // sort_sprites(cub);
    t_sprite    *sprite = ft_lstlast_sprite(cub->ray->sprites);
    float       mem_dist = 9999999;
    
    while (sprite)
    {
        if (sprite->dist < cub->ray->wall_dist && j > cub->mdata->screen[1] * 0.5 - sprite->height * 0.5 && j < cub->mdata->screen[1] * 0.5 + sprite->height * 0.5 && sprite->x_offset > 0 && sprite->x_offset < 1)
        {
            int pix_color;

            if (sprite->type == MONSTER)
                pix_color = ft_pix_color_calc_sprite(cub, sprite, j, cub->sprite);
            if (sprite->type == DOOR)
                pix_color = ft_pix_color_calc_sprite(cub, sprite, j, cub->door);
            if (pix_color > 0 && sprite->dist <= mem_dist)
            {
                if (cub->light == -1)
                    pix_color = ft_shade_color(pix_color, ft_flashlight(cub, sprite->dist * 1.1, i, j, MONSTER));
                ft_multi_pixel_put(cub, cub->img, i, j, ft_downscaling(cub, i, j), pix_color);
                mem_dist = sprite->dist;
            }
        }
        sprite = sprite->previous;
    }
}