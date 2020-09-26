/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:29:35 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/21 19:41:32 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				add_shade(double distance, int color)
{
	int			t;
	int			r;
	int			g;
	int			b;

	t = round((get_t(color) >> 24) * distance);
	r = round((get_r(color) >> 16) * distance);
	g = round((get_g(color) >> 8) * distance);
	b = round(get_b(color) * distance);
	return (create_trgb(t, r, g, b));
}

static void		fill_stripe_rectangle(double distance, t_rect *r, \
				t_vars *vars, int i)
{
	double		wall_height;
	double		dist_proj_plane;

	dist_proj_plane = (vars->map->w / 2) / tan(FOV_ANGLE / 2);
	wall_height = (MAP_SCALE / distance) * dist_proj_plane;
	r->x = i * WALL_STRIP_WIDTH;
	r->y = round((vars->map->h / 2) - (wall_height / 2));
	r->width = WALL_STRIP_WIDTH;
	r->height = round(wall_height);
}

void			render3d(t_vars *vars, t_rays **rays, int i)
{
	int			k;
	int			j;
	t_rect		r;

	while (i < vars->map->player.num_rays)
	{
		fill_stripe_rectangle(rays[i]->distance, &r, vars, i);
		k = r.x;
		while (k < r.x + r.width)
		{
			j = (r.y <= 0) ? 0 : r.y;
			while (j < r.y + r.height)
			{
				if (j >= vars->map->h)
					break ;
				set_color_from_wall(rays[i], vars, &r, j);
				r.color = add_shade(calc_shade(rays[i]->distance, vars), \
					r.color);
				my_mlx_pixel_put(&vars->img, k, j, r.color);
				j++;
			}
			k++;
		}
		i++;
	}
}
