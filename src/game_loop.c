/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:43:29 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/20 17:16:47 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_window_size(t_vars *vars)
{
	int x;
	int	y;

	mlx_get_screen_size(vars->mlx, &x, &y);
	if (vars->map->w > x)
		vars->map->w = x;
	if (vars->map->h > y)
		vars->map->h = y;
}

static void	init_texture(t_vars *vars, t_data *img)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, img->path, &img->width, \
			&img->height);
	if (!(img->img))
		exit_error(10);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
}

static void	init_textures(t_vars *vars)
{
	init_texture(vars, &vars->map->no);
	init_texture(vars, &vars->map->so);
	init_texture(vars, &vars->map->we);
	init_texture(vars, &vars->map->ea);
	init_texture(vars, &vars->map->s);
}

static void	init_img(t_vars *vars)
{
	if (vars->map->save_bmp == 0)
	{
		if (!(vars->win = mlx_new_window(vars->mlx, vars->map->w, \
			vars->map->h, "cub3D")))
			exit_error(3);
	}
	if (!(vars->img.img = mlx_new_image(vars->mlx, vars->map->w, vars->map->h)))
		exit_error(3);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
			&vars->img.bits_per_pixel, &vars->img.line_length, \
			&vars->img.endian);
}

void		game_loop(t_map *map)
{
	t_vars		*vars;

	if (!(vars = ft_calloc(1, sizeof(t_vars))))
		return ;
	vars->map = map;
	if (!(vars->mlx = mlx_init()))
		exit_error(3);
	check_window_size(vars);
	vars->map->player.num_rays = vars->map->w / WALL_STRIP_WIDTH;
	init_img(vars);
	init_textures(vars);
	update(vars);
	if (vars->map->save_bmp == 0)
	{
		mlx_hook(vars->win, 2, 1L << 0, &key_p, vars);
		mlx_hook(vars->win, 17, 1L << 17, &window_close, vars);
		mlx_loop_hook(vars->mlx, render_next_frame, vars);
		mlx_loop(vars->mlx);
	}
	free(vars);
}
