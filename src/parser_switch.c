/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:13:50 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/23 16:43:58 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_size(char *s, int i, t_map *map)
{
	char	*ds;
	int		j;

	if (!(ds = ft_strdup(s)))
		exit_error(3);
	while (ft_isspace(s[i]))
		i++;
	j = 0;
	while (ft_isdigit(s[i]))
		ds[j++] = s[i++];
	ds[j] = '\0';
	map->w = (ft_strlen(ds) > 4) ? 10000 : ft_atoi(ds);
	while (ft_isspace(s[i]))
		i++;
	j = 0;
	while (ft_isdigit(s[i]))
		ds[j++] = s[i++];
	ds[j] = '\0';
	map->h = (ft_strlen(ds) > 4) ? 10000 : ft_atoi(ds);
	free(ds);
	if (map->w == 0 || map->h == 0)
		exit_error(4);
	if (s[i] != '\0')
		exit_error(4);
}

char	*parse_path(char *s, int i)
{
	char	*ds;
	int		j;

	j = 0;
	if (!(ds = ft_strdup(s)))
		exit_error(3);
	while (ft_isspace(s[i]))
		i++;
	while (s[i] != '\0')
		ds[j++] = s[i++];
	ds[j] = '\0';
	return (ds);
}

int		get_color_number(char *s, int *ii)
{
	char	*ds;
	int		j;
	int		i;

	j = 0;
	i = *ii;
	if (!(ds = ft_strdup(s)))
		exit_error(3);
	while (ft_isdigit(s[i]))
		ds[j++] = s[i++];
	ds[j] = '\0';
	if (ft_strlen(ds) > 3 || ft_strlen(ds) == 0)
		exit_error(4);
	j = ft_atoi(ds);
	free(ds);
	*ii = i;
	if (j > 255 || j < 0)
		exit_error(4);
	return (j);
}

int		parse_color(char *s, int i)
{
	char	*ds;
	int		d;

	if (!(ds = ft_strdup(s)))
		exit_error(3);
	while (ft_isspace(s[i]))
		i++;
	d = get_color_number(s, &i) << 16;
	if (s[i] == ',')
		i++;
	else
		exit_error(4);
	d = d | get_color_number(s, &i) << 8;
	if (s[i] == ',')
		i++;
	else
		exit_error(4);
	d = d | get_color_number(s, &i);
	free(ds);
	if (s[i] != '\0')
		exit_error(4);
	return (d);
}

void	parser_switch(char *s, t_map *map, int i)
{
	if (s[i] == 'R' && !(map->w))
		parse_size(s, ++i, map);
	else if (s[i] == 'N' && s[i + 1] == 'O' && !(map->no.path))
		map->no.path = parse_path(s, i + 2);
	else if (s[i] == 'S' && s[i + 1] == 'O' && !(map->so.path))
		map->so.path = parse_path(s, i + 2);
	else if (s[i] == 'W' && s[i + 1] == 'E' && !(map->we.path))
		map->we.path = parse_path(s, i + 2);
	else if (s[i] == 'E' && s[i + 1] == 'A' && !(map->ea.path))
		map->ea.path = parse_path(s, i + 2);
	else if (s[i] == 'S' && s[i + 1] == ' ' && !(map->s.path))
		map->s.path = parse_path(s, ++i);
	else if (s[i] == 'F' && !(map->f))
		map->f = parse_color(s, ++i);
	else if (s[i] == 'C' && !(map->c))
		map->c = parse_color(s, ++i);
	else
		exit_error(4);
}
