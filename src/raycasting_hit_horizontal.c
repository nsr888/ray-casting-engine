/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hit_horizontal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:14:58 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/14 17:52:39 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double			get_yintercept_h(t_point *plr, double angle)
{
	double		yintercept;

	yintercept = floor(plr->y / MAP_SCALE) * MAP_SCALE;
	yintercept += is_ray_down(angle) ? MAP_SCALE : 0;
	return (yintercept);
}

double			get_ystep_h(double angle)
{
	double		ystep;

	ystep = MAP_SCALE;
	ystep *= !is_ray_down(angle) ? -1 : 1;
	return (ystep);
}

double			get_xstep_h(double angle)
{
	double		xstep;

	xstep = MAP_SCALE / tan(angle);
	xstep *= (!is_ray_right(angle) && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_right(angle) && xstep < 0) ? -1 : 1;
	return (xstep);
}

int				check_h_wall(double next_h_x, double next_h_y, \
				t_vars *vars, t_rays *ray_h)
{
	if (is_wall(\
		vars, next_h_x, next_h_y - (!is_ray_down(ray_h->angle) ? 1 : 0)))
	{
		ray_h->wall_hit_x = next_h_x;
		ray_h->wall_hit_y = next_h_y;
		return (1);
	}
	return (0);
}

void			get_distance_h(t_vars *vars, t_point *plr, double angle, \
				t_rays *ray_h)
{
	double		xstep;
	double		ystep;
	double		next_h_x;
	double		next_h_y;
	int			found_h;

	found_h = 0;
	ystep = get_ystep_h(angle);
	xstep = get_xstep_h(angle);
	next_h_y = get_yintercept_h(&vars->map->player, angle);
	next_h_x = plr->x + (next_h_y - plr->y) / tan(angle);
	ray_h->angle = angle;
	while (next_h_x >= 0 && next_h_x <= vars->map->cols * MAP_SCALE - 1 && \
			next_h_y >= 0 && next_h_y <= vars->map->rows * MAP_SCALE - 1)
	{
		if ((found_h = check_h_wall(next_h_x, next_h_y, vars, ray_h)))
			break ;
		else
		{
			next_h_x += xstep;
			next_h_y += ystep;
		}
	}
	ray_h->distance = (found_h) ? calc_dist(plr->x, plr->y, \
		ray_h->wall_hit_x, ray_h->wall_hit_y) : 2147483647;
}
