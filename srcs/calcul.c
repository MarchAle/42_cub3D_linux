#include "../includes/cub.h"

void    ft_init_calculs(t_cub *cub)
{
    cub->calc->half_height = cub->mdata->screen[1] * 0.5;
    cub->calc->half_width = cub->mdata->screen[0] * 0.5;
    cub->calc->alpha = ((180 - FOV) * 0.5) * M_PI / 180;
    cub->calc->cosalpha = cos(cub->calc->alpha);
    cub->calc->sinalpha = sin(cub->calc->alpha);
    cub->calc->d = cub->calc->half_width / cub->calc->cosalpha;
    cub->calc->powd = pow(cub->calc->d, 2);
    cub->calc->fovHalf = (FOV * M_PI / 180) * 0.5;
    cub->calc->piHalf = M_PI * 0.5;
    cub->calc->max_vignet = sqrtf(powf(cub->calc->half_height, 2) + powf(cub->calc->half_width, 2));
}

void    ft_trigo_angle(t_cub *cub)
{
    cub->calc->cosAngle = cos(cub->ray->angle);
    cub->calc->sinAngle = sin(cub->ray->angle);
    cub->calc->tanAngle = tan(cub->ray->angle);
}