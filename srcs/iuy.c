void    ft_sprites_calc(t_ray *ray)
{
    t_sprite *sprite = ray->sprites;

    while (sprite)
    {
        sprite->to_display = TRUE;
        
        sprite = sprite->next;
    }
}