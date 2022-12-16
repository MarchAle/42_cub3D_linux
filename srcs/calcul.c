#include "../includes/cub.h"

float	ft_angleCalculation(int i, t_cub *cub)
{
	float a = sqrtf(pow(i, 2) + cub->calc->powd - (2 * i * cub->calc->d * cub->calc->cosalpha));
	float angle = asin(cub->calc->sinalpha * i / a);
	return (angle);
}

void    init_angles(t_cub *cub)
{
    float   *angles = malloc(sizeof(float) * cub->mdata->screen[0]);
    int     i = cub->mdata->screen[0];
    while (i >= 0)
    {
        angles[i] = ft_angleCalculation(i, cub);
        i--;
    }
    cub->angles = angles;
}

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
    init_angles(cub);
}

void    ft_trigo_angle(t_ray *ray)
{
    ray->cosAngle = cos(ray->angle);
    ray->sinAngle = sin(ray->angle);
    ray->tanAngle = tan(ray->angle);
}