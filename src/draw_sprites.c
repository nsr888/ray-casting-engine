/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 21:01:19 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/15 13:11:47 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		sort_sprites_bubble(t_sprites *sprites, int cnt)
{
	t_sprites	swap;
	int			i;
	int			swapped;

	swapped = 1;
	while (swapped)
	{
		i = 0;
		swapped = 0;
		while (i < cnt - 1)
		{
			if (sprites[i].distance < sprites[i + 1].distance)
			{
				swap = sprites[i];
				sprites[i] = sprites[i + 1];
				sprites[i + 1] = swap;
				swapped = 1;
			}
			i++;
		}
	}
}

void			calc_sprites_distance(t_vars *vars)
{
	int			i;
	int			count;
	double		dist_proj_plane;
	t_sprites	*sprites;
	t_point		*plr;

	plr = &vars->map->player;
	count = vars->map->sprites_num;
	sprites = vars->map->sprites;
	dist_proj_plane = (vars->map->w / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while (i < count)
	{
		sprites[i].angle = norm_angle(atan2(sprites[i].y - plr->y, \
			sprites[i].x - plr->x) - norm_angle(plr->angle));
		sprites[i].distance = calc_dist(plr->x, plr->y, sprites[i].x, \
			sprites[i].y);
		sprites[i].size = (MAP_SCALE / sprites[i].distance) * dist_proj_plane;
		i++;
	}
}

void			draw_sprites(t_vars *vars, t_rays **rays)
{
	calc_sprites_distance(vars);
	sort_sprites_bubble(vars->map->sprites, vars->map->sprites_num);
	render_sprites(vars, rays);
}
