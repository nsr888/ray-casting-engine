/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:31:01 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/14 22:50:19 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_p(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 13)
		vars->map->player.walk_direction = 1;
	else if (keycode == 1)
		vars->map->player.walk_direction = -1;
	else if (keycode == 0)
		vars->map->player.strafe = -1;
	else if (keycode == 2)
		vars->map->player.strafe = 1;
	else if (keycode == 123)
		vars->map->player.turn_direction = -1;
	else if (keycode == 124)
		vars->map->player.turn_direction = 1;
	return (1);
}

int		key_r(int keycode, t_vars *vars)
{
	vars->key_time = 0;
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (1);
}

int		window_close(void)
{
	exit(0);
}
