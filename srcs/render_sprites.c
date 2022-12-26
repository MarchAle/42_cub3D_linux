#include "../includes/cub.h"

void    ft_sprites_calc(t_cub *cub, t_ray *ray)
{
    t_sprite *sprite = ray->sprites;

    while (sprite)
    {
        sprite->to_display = TRUE;
        if (sprite->type == MONSTER || sprite->type == KEY || sprite->type == POTION)
        {
            float x =  sprite->x - cub->player->x;
            float y =  sprite->y - cub->player->y;

            float nx = x * cos(cub->player->orient) - y * sin(cub->player->orient);
            float ny = x * sin(cub->player->orient) + y * cos(cub->player->orient);

            float ray_sprite_offset = (ny - (tan(ray->angle_player) * nx))* -1 + 0.5;

            sprite->x_offset = ray_sprite_offset;
            sprite->height = HEIGHT_RATIO / nx * cub->mdata->screen[1];
            sprite->dist = nx;
        }
        else if (sprite->type == DOOR)
        {
            sprite->height = (HEIGHT_RATIO / (sprite->dist * cos(cub->player->orient - ray->angle))) * cub->mdata->screen[1];

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
        if (sprite_offset_y > tex->height[0] || sprite_offset_y < 0)
            return (color);
        color = ft_get_color_from_texture(tex, (int)(sprite->x_offset * tex->width[0]),	(int)sprite_offset_y);
    }
	return (color);
}

int     get_door_color(t_cub *cub, t_sprite *sprite, int j)
{
	t_door *door = cub->doors;

    while (door)
    {
        if (door->x == sprite->x && door->y == sprite->y)
        {
            if (door->locked == 1)
                return (ft_pix_color_calc_sprite(cub, sprite, j, cub->door_locked));
            else
                return (ft_pix_color_calc_sprite(cub, sprite, j, cub->door));
        }
        door = door->next;
    }
    return (0);
}

void    ft_render_sprites(t_cub *cub, t_ray *ray, int i, int j)
{
    t_sprite    *sprite = ft_lstlast_sprite(ray->sprites);
    float       mem_dist = 9999999;
    
    while (sprite)
    {
        if (sprite->dist < ray->wall_dist && j > cub->mdata->screen[1] * 0.5 - sprite->height * 0.5 && j < cub->mdata->screen[1] * 0.5 + sprite->height * 0.5 && sprite->x_offset > 0 && sprite->x_offset < 1)
        {
            int pix_color;

            if (sprite->type == MONSTER)
                pix_color = ft_pix_color_calc_sprite(cub, sprite, j, cub->sprite);
            if (sprite->type == POTION)
                pix_color = ft_pix_color_calc_sprite(cub, sprite, j, cub->potion);
            if (sprite->type == KEY)
                pix_color = ft_pix_color_calc_sprite(cub, sprite, j - (cub->key_vertical * sprite->height * 0.2), cub->key);
            if (sprite->type == DOOR)
                pix_color = get_door_color(cub, sprite, j);
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