/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:13:10 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/22 08:39:55 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		draw_rect(t_rect *rect, t_data *img)
{
	int		i;
	int		j;
	int		max_x;
	int		max_y;

	i = rect->x;
	max_x = rect->x + rect->width;
	while (i < max_x)
	{
		j = rect->y;
		max_y = rect->y + rect->height;
		while (j < max_y)
		{
			my_mlx_pixel_put(img, i, j, rect->color);
			j++;
		}
		i++;
	}
}

void		draw_square_from_center(t_rect r, t_data *img)
{
	int		i;
	int		j;
	int		max_i;
	int		max_j;

	i = r.x - r.width / 2;
	max_i = r.x + r.width / 2;
	while (i < max_i)
	{
		j = r.y - r.width / 2;
		max_j = r.y + r.width / 2;
		while (j < max_j)
		{
			my_mlx_pixel_put(img, i, j, r.color);
			j++;
		}
		i++;
	}
}

void		draw_square(t_rect r, t_data *img)
{
	int		i;
	int		j;
	int		max_i;
	int		max_j;

	i = r.x;
	max_i = r.x + r.width;
	while (i < max_i)
	{
		j = r.y;
		max_j = r.y + r.width;
		while (j < max_j)
		{
			my_mlx_pixel_put(img, i, j, r.color);
			j++;
		}
		i++;
	}
}
