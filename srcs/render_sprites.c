#include "../includes/cub.h"

void    ft_sprites_calc(t_cub *cub)
{
    t_sprite *sprite = cub->ray->sprites;
    int i = 1;
    while (sprite)
    {
        // float   dist = sqrtf(pow(sprite->x - cub->player->x, 2) + pow(sprite->y - cub->player->y, 2));
        // float   adjacent = fabsf(cub->ray->x - cub->player->x);
        // float   angle_horizontal = acos(adjacent / dist);
        // float   angle_player_sprite = angle_horizontal - cub->player->orient;
        // float   angle_sprite_perp = M_PI * 0.5 - angle_player_sprite;
        // float   angle_ray_sprite = angle_player_sprite - cub->ray->angle;
        // float   dist_ray_perp = (dist * sin(angle_ray_sprite)) / sin(angle_ray_sprite + angle_sprite_perp);
        // float   dist_sprite_perp = (dist * sin(angle_sprite_perp)) / sin(angle_ray_sprite + angle_sprite_perp);

        // float   sprite_height = (1 / dist_ray_perp) * cub->mdata->screen[1];

        // sprite->x_offset = dist_sprite_perp;
        // sprite->height = sprite_height;


        float x =  sprite->x - cub->player->x;
        float y =  sprite->y - cub->player->y;

        float nx = x * cos(cub->player->orient) - y * sin(cub->player->orient);
        float ny = x * sin(cub->player->orient) + y * cos(cub->player->orient);

        float ray_sprite_offset = (ny - (tan(cub->ray->angle_player) * nx))* -1 + 0.5; //

        // if (cub->ray->angle > cub->player->orient - M_PI / 90 && cub->ray->angle < cub->player->orient + M_PI / 90)
        //     printf("ici %d, dist : %f, nx : %f ny : %f player x : %f y : %f sprite x : %f y : %f, offset : %f\n", i, dist, nx, ny, cub->player->x, cub->player->y, sprite->x, sprite->y, ray_sprite_offset);

        sprite->x_offset = ray_sprite_offset;
        sprite->height = 1 / nx * cub->mdata->screen[1];
        sprite->dist = nx;
        // if (cub->ray->angle > cub->player->orient - M_PI / 90 && cub->ray->angle < cub->player->orient + M_PI / 90)
        //     printf("x_offset : %f\n", sprite->x_offset);
        sprite = sprite->next;
        i++;
    }
}

int ft_pix_color_calc_sprite(t_cub *cub, t_sprite *sprite, int j, t_texture *tex)
{
	int	color;

    float sprite_offset_y = (float)((j - ((cub->mdata->screen[1] - sprite->height) / 2))
			/ (sprite->height) * tex->height[0]);

	color = ft_get_color_from_texture(tex, (int)(sprite->x_offset * tex->width[0]),	(int)sprite_offset_y);
    // printf("color calc\n");
    
    // printf("ici color : %d\n", color);

	return (color);
}

void    ft_render_sprites(t_cub *cub, int i, int j)
{
    t_sprite *sprite = ft_lstlast(cub->ray->sprites);
    int k = 1;
    while (sprite)
    {
        if (j > cub->mdata->screen[1] * 0.5 - sprite->height * 0.5 && j < cub->mdata->screen[1] * 0.5 + sprite->height * 0.5 && sprite->x_offset > 0 && sprite->x_offset < 1)
        {
            int pix_color;
            pix_color = ft_pix_color_calc_sprite(cub, sprite, j, cub->sprite);
            if (pix_color > 0)
            {
                if (cub->light == -1)
                    pix_color = ft_shade_color(pix_color, sprite->dist);
                my_mlx_pixel_put(cub->img, i, j, pix_color);
                my_mlx_pixel_put(cub->img, i + 1, j, pix_color);
                my_mlx_pixel_put(cub->img, i, j + 1, pix_color);
                my_mlx_pixel_put(cub->img, i + 1, j + 1, pix_color);
            }
        }
        sprite = sprite->previous;
        k++;
    }
}