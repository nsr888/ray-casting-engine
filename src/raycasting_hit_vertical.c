/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hit_vertical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:00:27 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/14 17:51:48 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double			get_xintercept_v(t_point *plr, double angle)
{
	double		xintercept;

	xintercept = floor(plr->x / MAP_SCALE) * MAP_SCALE;
	xintercept += is_ray_right(angle) ? MAP_SCALE : 0;
	return (xintercept);
}

double			get_ystep_v(double angle)
{
	double		ystep;

	ystep = MAP_SCALE * tan(angle);
	ystep *= (!is_ray_down(angle) && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_down(angle) && ystep < 0) ? -1 : 1;
	return (ystep);
}

double			get_xstep_v(double angle)
{
	double		xstep;

	xstep = MAP_SCALE;
	xstep *= !is_ray_right(angle) ? -1 : 1;
	return (xstep);
}

int				check_v_wall(double next_v_x, double next_v_y, \
				t_vars *vars, t_rays *ray_v)
{
	if (is_wall(\
		vars, next_v_x - (!is_ray_right(ray_v->angle) ? 1 : 0), next_v_y))
	{
		ray_v->wall_hit_x = next_v_x;
		ray_v->wall_hit_y = next_v_y;
		return (1);
	}
	return (0);
}

void			get_distance_v(t_vars *vars, t_point *plr, double angle, \
				t_rays *ray_v)
{
	double		xstep;
	double		ystep;
	double		next_v_x;
	double		next_v_y;
	int			found_v;

	found_v = 0;
	ystep = get_ystep_v(angle);
	xstep = get_xstep_v(angle);
	next_v_x = get_xintercept_v(&vars->map->player, angle);
	next_v_y = plr->y + (next_v_x - plr->x) * tan(angle);
	ray_v->angle = angle;
	while (next_v_x >= 0 && next_v_x <= vars->map->cols * MAP_SCALE - 1 && \
			next_v_y >= 0 && next_v_y <= vars->map->rows * MAP_SCALE - 1)
	{
		if ((found_v = check_v_wall(next_v_x, next_v_y, vars, ray_v)))
			break ;
		else
		{
			next_v_x += xstep;
			next_v_y += ystep;
		}
	}
	ray_v->distance = (found_v) ? calc_dist(plr->x, plr->y, \
		ray_v->wall_hit_x, ray_v->wall_hit_y) : 2147483647;
}
