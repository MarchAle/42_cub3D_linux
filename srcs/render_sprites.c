#include "../includes/cub.h"

void    ft_sprites_calc(t_cub *cub)
{
    t_sprite *sprite = cub->ray->sprites;
    while (sprite)
    {
        float x =  sprite->x - cub->player->x;
        float y =  sprite->y - cub->player->y;

        float nx = x * cos(cub->player->orient) - y * sin(cub->player->orient);
        float ny = x * sin(cub->player->orient) + y * cos(cub->player->orient);

        float ray_sprite_offset = (ny - (tan(cub->ray->angle_player) * nx))* -1 + 0.5;

        sprite->x_offset = ray_sprite_offset;
        sprite->height = 1 / nx * cub->mdata->screen[1];
        sprite->dist = nx;
        sprite = sprite->next;
    }
}

int ft_pix_color_calc_sprite(t_cub *cub, t_sprite *sprite, int j, t_texture *tex)
{
	int	color;

    float sprite_offset_y = (float)((j - ((cub->mdata->screen[1] - sprite->height) / 2))
			/ (sprite->height) * tex->height[0]);
	color = ft_get_color_from_texture(tex, (int)(sprite->x_offset * tex->width[0]),	(int)sprite_offset_y);
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
                {
                    // pix_color = ft_shade_color(pix_color, sprite->dist * 1.2);
                    float dist_vignet = sqrtf(powf(cub->calc->half_height - j, 2) + powf(cub->calc->half_width - i, 2));
		            dist_vignet = dist_vignet / cub->calc->max_vignet;
                    // if (sprite->dist < 3)
                    //     dist_vignet = dist_vignet - ((sprite->dist) / 3 * sprite->dist) * 0.2;
                    // if (dist_vignet < 0)
			        //     dist_vignet = 0;
	            	pix_color = ft_shade_color(pix_color, (sprite->dist * 1.1 < 1.5 ? 0 : (sprite->dist * 1.1 - 1.5) * 0.7) + (dist_vignet < 0.3 ? 0 : (dist_vignet - 0.3) * 13));
                }
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