/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 19:23:28 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/21 19:54:42 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clear_map(t_vars *vars)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = vars->map->w;
	rect.height = vars->map->h / 2;
	rect.color = vars->map->c;
	draw_rect(&rect, &vars->img);
	rect.y = vars->map->h / 2;
	rect.width = vars->map->w;
	rect.height = vars->map->h / 2;
	rect.color = vars->map->f;
	draw_rect(&rect, &vars->img);
}

static void	free_rays(t_vars *vars, t_rays **rays)
{
	int	i;

	i = -1;
	while (++i < vars->map->player.num_rays)
		free(rays[i]);
}

void		update(t_vars *vars)
{
	t_rays	**rays;

	clear_map(vars);
	change_player_coord(vars);
	rays = cast_all_rays(vars);
	render3d(vars, rays, 0);
	draw_sprites(vars, rays);
	if (vars->map->cols * MAP_SCALE * MINIMAP_SCALE < vars->map->w && \
			vars->map->rows * MAP_SCALE * MINIMAP_SCALE < vars->map->h)
	{
		draw_map(vars->map->content, vars);
		draw_minimap_rays(vars, rays);
	}
	free_rays(vars, rays);
	free(rays);
	if (vars->map->save_bmp == 1)
		save_bmp(vars->img, vars->map->w, vars->map->h, 0);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int			render_next_frame(t_vars *vars)
{
	if (vars->map->player.walk_direction != 0 || \
			vars->map->player.strafe != 0 || \
			vars->map->player.turn_direction != 0)
	{
		mlx_sync(1, vars->img.img);
		update(vars);
		mlx_sync(3, vars->win);
	}
	return (0);
}
