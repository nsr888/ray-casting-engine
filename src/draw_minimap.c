/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 18:59:24 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/15 00:19:15 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_player_point_on_minimap(t_vars *vars)
{
	t_rect	r;

	r.x = round(vars->map->player.x * MINIMAP_SCALE);
	r.y = round(vars->map->player.y * MINIMAP_SCALE);
	r.color = 0x00FF0000;
	r.width = 32 * MINIMAP_SCALE;
	if (r.x < vars->map->w && r.y < vars->map->h)
		draw_square_from_center(r, &vars->img);
}

void		draw_map(char **content, t_vars *vars)
{
	int		x;
	int		y;
	t_rect	r;

	y = 0;
	while (content[y])
	{
		x = 0;
		while (content[y][x])
		{
			r.x = x * MAP_SCALE * MINIMAP_SCALE;
			r.y = y * MAP_SCALE * MINIMAP_SCALE;
			if (r.x < vars->map->w && r.y < vars->map->h)
			{
				r.color = (content[y][x] == '1' || content[y][x] == '2') ? \
					vars->map->f : 0x00FFFFFF;
				r.width = MAP_SCALE * MINIMAP_SCALE;
				if (content[y][x] != ' ')
					draw_square(r, &vars->img);
			}
			x++;
		}
		y++;
	}
	draw_player_point_on_minimap(vars);
}

static void	calc_delta_and_steep(t_rect *delta, t_rect *steep, \
			t_rect p0, t_rect p1)
{
	delta->x = abs(p1.x - p0.x);
	steep->x = p0.x < p1.x ? 1 : -1;
	delta->y = abs(p1.y - p0.y);
	steep->y = p0.y < p1.y ? 1 : -1;
}

/*
** Bresenham's line algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/

void		draw_line(t_data *img, t_rect p0, t_rect p1)
{
	t_rect	delta;
	t_rect	steep;
	int		err;
	int		e2;

	calc_delta_and_steep(&delta, &steep, p0, p1);
	err = (delta.x > delta.y ? delta.x : -delta.y) / 2;
	while (1)
	{
		my_mlx_pixel_put(img, p0.x, p0.y, 0x00444444);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = err;
		if (e2 > -delta.x)
		{
			err -= delta.y;
			p0.x += steep.x;
		}
		if (e2 < delta.y)
		{
			err += delta.x;
			p0.y += steep.y;
		}
	}
}

void		draw_minimap_rays(t_vars *vars, t_rays **rays)
{
	int		i;
	t_rect	plr_coord;
	t_rect	wall_coord;

	i = 0;
	while (i < vars->map->player.num_rays)
	{
		plr_coord.x = vars->map->player.x * MINIMAP_SCALE;
		plr_coord.y = vars->map->player.y * MINIMAP_SCALE;
		wall_coord.x = rays[i]->wall_hit_x * MINIMAP_SCALE;
		wall_coord.y = rays[i]->wall_hit_y * MINIMAP_SCALE;
		draw_line(&vars->img, plr_coord, wall_coord);
		i++;
	}
}
