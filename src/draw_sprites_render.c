/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:07:22 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/15 13:18:04 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		fill_sprite_stripe_rectangle(t_sprites sprite, t_rect *r, \
				t_vars *vars)
{
	double		dist_proj_plane;
	double		sprite_tmp_x;

	dist_proj_plane = (vars->map->w / 2) / tan(FOV_ANGLE / 2);
	r->height = round(sprite.size);
	r->width = round(sprite.size);
	sprite_tmp_x = tan(sprite.angle) * dist_proj_plane;
	r->x = round(vars->map->w / 2 + sprite_tmp_x - sprite.size / 2);
	r->y = round((vars->map->h - sprite.size) / 2);
}

static double	norm_distance(t_sprites sprite, t_rays *ray, \
				t_vars *vars)
{
	return (sprite.distance * cos(norm_angle(ray->angle) - \
						norm_angle(vars->map->player.angle)));
}

static void		render_sprites_pixels(t_rect r, t_sprites s, \
				t_rays **rays, t_vars *vars)
{
	int			k;
	int			j;
	double		dist_norm;

	k = (r.x <= 0) ? 0 : r.x;
	while (k < r.width + r.x)
	{
		if (k >= vars->map->w)
			break ;
		dist_norm = norm_distance(s, rays[k], vars);
		j = (r.y <= 0) ? 0 : r.y;
		while (j < r.height + r.y)
		{
			if (j < vars->map->h && rays[k]->distance > dist_norm)
			{
				r.color = get_color_sprite(vars->map->s, r, k, j);
				if (get_t(r.color) == 0)
					my_mlx_pixel_put(&vars->img, k, j, \
							add_shade(calc_shade(s.distance, vars), r.color));
			}
			j++;
		}
		k++;
	}
}

void			render_sprites(t_vars *vars, t_rays **rays)
{
	int			i;
	t_sprites	*sprites;
	t_rect		r;

	sprites = vars->map->sprites;
	i = 0;
	while (i < vars->map->sprites_num)
	{
		fill_sprite_stripe_rectangle(sprites[i], &r, vars);
		if (sprites[i].angle > 5 * FOV_ANGLE || sprites[i].angle < FOV_ANGLE)
		{
			render_sprites_pixels(r, sprites[i], rays, vars);
		}
		i++;
	}
}
