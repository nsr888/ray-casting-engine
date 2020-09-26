/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:08:22 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/20 17:35:42 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_angle_by_char(char c)
{
	if (c == 'S')
		return (M_PI / 2);
	else if (c == 'W')
		return (M_PI);
	else if (c == 'N')
		return (M_PI + (M_PI / 2));
	return (0);
}

static void		fill_player_struct(t_map *map, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (map->player.x)
			exit_error(4);
		map->player.angle = get_angle_by_char(c);
		map->player.walk_direction = 0;
		map->player.strafe = 0;
		map->player.x = x * MAP_SCALE + MAP_SCALE / 2;
		map->player.y = y * MAP_SCALE + MAP_SCALE / 2;
	}
}

static void		fill_sprites_struct(t_map *map, unsigned int col, \
		unsigned int row, int *ii)
{
	int		i;

	if (map->content[row][col] == '2')
	{
		i = *ii;
		map->sprites[i].x = col * MAP_SCALE + MAP_SCALE / 2;
		map->sprites[i].y = row * MAP_SCALE + MAP_SCALE / 2;
		i++;
		*ii = i;
	}
}

static void		map_chars_validate(char c)
{
	if (!(c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0' || \
				c == '1' || c == '2' || c == ' '))
	{
		exit_error(4);
	}
}

void			map_fill_content(t_list *lst, t_map *map, unsigned int col, \
		unsigned int row)
{
	int		i;

	i = 0;
	while (lst)
	{
		if (((char *)lst->content)[0] == '\0')
			break ;
		col = -1;
		while (++col < map->cols)
		{
			if (col >= ft_strlen(lst->content))
				map->content[row][col] = ' ';
			else
			{
				map->content[row][col] = ((char *)lst->content)[col];
				map_chars_validate(((char *)lst->content)[col]);
				fill_player_struct(map, ((char *)lst->content)[col], col, row);
				fill_sprites_struct(map, col, row, &i);
			}
		}
		map->content[row][col] = '\0';
		lst = lst->next;
		row++;
	}
	map->content[row] = NULL;
}
