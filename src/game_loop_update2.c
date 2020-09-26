/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_update2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 19:27:07 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/14 21:23:06 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_sprite(t_vars *vars, double x, double y)
{
	int		xm;
	int		ym;

	if (x < 0 || x > vars->map->cols * MAP_SCALE - 1 || y < 0 || \
			y > vars->map->rows * MAP_SCALE - 1)
		return (1);
	xm = floor(x / MAP_SCALE);
	ym = floor(y / MAP_SCALE);
	if (vars->map->content[ym][xm] == '2')
		return (1);
	return (0);
}

int			is_wall(t_vars *vars, double x, double y)
{
	int		xm;
	int		ym;

	if (x < 0 || x > vars->map->cols * MAP_SCALE - 1 || y < 0 || \
			y > vars->map->rows * MAP_SCALE - 1)
		return (1);
	xm = floor(x / MAP_SCALE);
	ym = floor(y / MAP_SCALE);
	if (vars->map->content[ym][xm] == '1')
		return (1);
	return (0);
}

static void	set_coord_if_no_wall(t_vars *vars, double xn, double yn)
{
	t_point	*plr;

	plr = &vars->map->player;
	if (!is_wall(vars, xn, yn) && !is_sprite(vars, xn, yn))
	{
		plr->x = xn;
		plr->y = yn;
	}
}

void		change_player_coord(t_vars *vars)
{
	t_point	*plr;
	double	xn;
	double	yn;

	plr = &vars->map->player;
	if (plr->walk_direction != 0)
	{
		xn = plr->x + cos(plr->angle) * (WALK_SPD * plr->walk_direction);
		yn = plr->y + sin(plr->angle) * (WALK_SPD * plr->walk_direction);
		set_coord_if_no_wall(vars, xn, yn);
		plr->walk_direction = 0;
	}
	if (plr->strafe != 0)
	{
		xn = plr->x + cos(plr->angle + (M_PI / 2)) * (WALK_SPD * plr->strafe);
		yn = plr->y + sin(plr->angle + (M_PI / 2)) * (WALK_SPD * plr->strafe);
		set_coord_if_no_wall(vars, xn, yn);
		plr->strafe = 0;
	}
	if (plr->turn_direction != 0)
	{
		plr->angle = plr->angle + (plr->turn_direction * ROTATION_SPEED);
		plr->turn_direction = 0;
	}
}
