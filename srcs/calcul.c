#include "../includes/cub.h"

void    ft_init_calculs(t_cub *cub)
{
    cub->calc->alpha = ((180 - FOV) * 0.5) * M_PI / 180;
    cub->calc->cosalpha = cos(cub->calc->alpha);
    cub->calc->sinalpha = sin(cub->calc->alpha);
    cub->calc->d = (cub->mdata->screen[0] * 0.5) / cub->calc->cosalpha;
    cub->calc->powd = pow(cub->calc->d, 2);
    cub->calc->fovHalf = (FOV * M_PI / 180) * 0.5;
    cub->calc->piHalf = M_PI * 0.5;

}

void    ft_trigo_angle(t_cub *cub)
{
    cub->calc->cosAngle = cos(cub->ray->angle);
    cub->calc->sinAngle = sin(cub->ray->angle);
    cub->calc->tanAngle = tan(cub->ray->angle);
}