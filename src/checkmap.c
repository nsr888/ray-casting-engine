/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:23:46 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/23 17:50:57 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		check_boundaries(t_map *map, int x, int y)
{
	if (x < 0 || (x >= 0 && ((unsigned int)x >= map->cols)) \
		|| y < 0 || (y >= 0 && ((unsigned int)y >= map->rows)))
		exit_error(4);
}

static void		flood(t_map *map, int x, int y, char fields[4])
{
	char	c;

	check_boundaries(map, x, y);
	c = map->content[y][x];
	if (c != '1' && c != fields[2] && c != fields[3])
	{
		if (c == ' ')
			exit_error(4);
		if (!(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		{
			if (c == fields[0] || c == ' ')
				map->content[y][x] = fields[2];
			if (c == fields[1])
				map->content[y][x] = fields[3];
		}
		flood(map, x + 1, y, fields);
		flood(map, x + 1, y + 1, fields);
		flood(map, x + 1, y - 1, fields);
		flood(map, x - 1, y, fields);
		flood(map, x - 1, y + 1, fields);
		flood(map, x - 1, y - 1, fields);
		flood(map, x, y + 1, fields);
		flood(map, x, y - 1, fields);
	}
}

void			valid_map_check(t_map *map)
{
	if (!(map->w) || !(map->h))
		exit_error(4);
	if (map->w == -1 || map->h == -1)
		exit_error(4);
	if (!(map->no.path) || !(map->so.path) || !(map->we.path) || \
			!(map->ea.path) || !(map->s.path))
	{
		exit_error(4);
	}
	if (!(map->f) || !(map->c))
		exit_error(4);
}

/*
** 1) Flood fill and check for going out of boundaries
** 2) Invert flood fill.
*/

int				check_map(t_map *map)
{
	unsigned int	player_col;
	unsigned int	player_row;

	if (!(map->player.x))
		exit_error(4);
	valid_map_check(map);
	player_col = round((map->player.x - MAP_SCALE / 2) / MAP_SCALE);
	player_row = round((map->player.y - MAP_SCALE / 2) / MAP_SCALE);
	flood(map, player_col, player_row, "0234");
	flood(map, player_col, player_row, "3402");
	return (1);
}
