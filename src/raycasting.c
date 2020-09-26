/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 09:45:11 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/23 16:48:49 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_ray_wall_type(t_rays **rays, double angle, \
			int was_hit_vertical)
{
	if (is_ray_down(angle) && !was_hit_vertical)
		(*rays)->wall_type = 'S';
	else if (!is_ray_down(angle) && !was_hit_vertical)
		(*rays)->wall_type = 'N';
	else if (is_ray_right(angle) && was_hit_vertical)
		(*rays)->wall_type = 'E';
	else
		(*rays)->wall_type = 'W';
}

static void	cast_ray(t_vars *vars, t_point *plr, double angle, t_rays **rays)
{
	t_rays	ray_h;
	t_rays	ray_v;

	get_distance_h(vars, &vars->map->player, angle, &ray_h);
	get_distance_v(vars, &vars->map->player, angle, &ray_v);
	if (ray_h.distance < ray_v.distance)
	{
		(*rays)->wall_hit_x = round(ray_h.wall_hit_x);
		(*rays)->wall_hit_y = round(ray_h.wall_hit_y);
		(*rays)->distance = ray_h.distance * cos(angle - plr->angle);
		(*rays)->was_hit_vertical = 0;
	}
	else
	{
		(*rays)->wall_hit_x = round(ray_v.wall_hit_x);
		(*rays)->wall_hit_y = round(ray_v.wall_hit_y);
		(*rays)->distance = ray_v.distance * cos(angle - plr->angle);
		(*rays)->was_hit_vertical = 1;
	}
	(*rays)->angle = angle;
	set_ray_wall_type(rays, angle, (*rays)->was_hit_vertical);
}

t_rays		**cast_all_rays(t_vars *vars)
{
	t_point	*plr;
	t_rays	**rays;
	double	angle;
	int		num_rays;
	int		i;

	plr = &vars->map->player;
	angle = plr->angle - (FOV_ANGLE / 2);
	num_rays = vars->map->player.num_rays;
	if (!(rays = malloc(num_rays * sizeof(*rays))))
		exit_error(3);
	i = 0;
	while (i < num_rays)
	{
		if (!(rays[i] = malloc(1 * sizeof(**rays))))
			exit_error(3);
		cast_ray(vars, plr, norm_angle(angle), &rays[i]);
		angle += FOV_ANGLE / num_rays;
		i++;
	}
	return (rays);
}
