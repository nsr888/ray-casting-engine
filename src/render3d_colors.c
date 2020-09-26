/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 21:12:26 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/14 22:55:09 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		get_color_from_pixel(t_data *img, int x, int y)
{
	int			c[4];

	c[0] = img->addr[(y * img->line_length + x * (img->bits_per_pixel / 8) + \
		0)] & 0x000000FF;
	c[1] = img->addr[(y * img->line_length + x * (img->bits_per_pixel / 8) + \
		1)] & 0x000000FF;
	c[2] = img->addr[(y * img->line_length + x * (img->bits_per_pixel / 8) + \
		2)] & 0x000000FF;
	c[3] = (img->addr[(y * img->line_length + x * (img->bits_per_pixel / 8) + \
		3)] & 0x00FF0000) >> 16;
	return (create_trgb(c[3], c[2], c[1], c[0]));
}

int				get_color_sprite(t_data img, t_rect r, int k, int j)
{
	int			x;
	int			y;

	x = ((k - r.x) * img.width) / r.width;
	y = ((j - r.y) * img.height) / r.height;
	return (get_color_from_pixel(&img, x, y));
}

int				get_color(t_data *img, t_rays *rays, t_rect *r, int j)
{
	int			x;
	int			y;

	if (rays->was_hit_vertical == 0)
		x = round((int)round(rays->wall_hit_x) % img->width);
	else
		x = round((int)round(rays->wall_hit_y) % img->width);
	y = ((j - r->y) * img->height) / r->height;
	return (get_color_from_pixel(img, x, y));
}

double			calc_shade(double distance, t_vars *vars)
{
	int			map_max;
	double		shade_coef;

	map_max = (vars->map->rows > vars->map->cols) ? vars->map->rows : \
		vars->map->cols;
	shade_coef = 1 - distance / (map_max * MAP_SCALE);
	return (shade_coef);
}

void			set_color_from_wall(t_rays *rays, t_vars *vars, t_rect *r, \
				int j)
{
	if (rays->wall_type == 'S')
		r->color = get_color(&vars->map->so, rays, r, j);
	else if (rays->wall_type == 'N')
		r->color = get_color(&vars->map->no, rays, r, j);
	else if (rays->wall_type == 'E')
		r->color = get_color(&vars->map->ea, rays, r, j);
	else
		r->color = get_color(&vars->map->we, rays, r, j);
}
