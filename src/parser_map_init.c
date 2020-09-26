/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 17:41:40 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/20 17:59:03 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		get_sprites_count(t_list *lst)
{
	int		sprites_num;
	int		x;
	char	*s;

	if (!lst)
		return (0);
	sprites_num = 0;
	while (lst)
	{
		x = 0;
		s = lst->content;
		while (s[x])
		{
			if (s[x] == '2')
				sprites_num++;
			x++;
		}
		lst = lst->next;
	}
	return (sprites_num);
}

static int		get_max_line(t_list *lst)
{
	int		max;
	int		len;

	if (!lst)
		exit_error(4);
	max = 0;
	while (lst && ((char *)lst->content)[0] != '\0')
	{
		len = ft_strlen(lst->content);
		max = (len > max) ? len : max;
		lst = lst->next;
	}
	return (max);
}

static int		count_lst_rows(t_list *lst)
{
	int		rows;

	if (!lst)
		exit_error(4);
	rows = 0;
	while (lst && ((char *)lst->content)[0] != '\0')
	{
		rows++;
		lst = lst->next;
	}
	if (((char *)lst->content)[0] == '\0')
	{
		while (lst)
		{
			if (((char *)lst->content)[0] != '\0')
				exit_error(4);
			lst = lst->next;
		}
	}
	return (rows);
}

void			map_init_and_allocate(t_list *lst, t_map *map)
{
	unsigned int	i;

	map->sprites_num = get_sprites_count(lst);
	map->rows = count_lst_rows(lst);
	map->cols = get_max_line(lst);
	if (!(map->sprites = malloc(map->sprites_num * sizeof(t_sprites))))
		exit_error(3);
	if (!(map->content = ft_calloc(map->rows + 1, sizeof(*map->content))))
		exit_error(3);
	i = 0;
	while (i < map->rows)
	{
		if (!(map->content[i] = ft_calloc(map->cols + 1, \
						sizeof(**map->content))))
			exit_error(3);
		i++;
	}
}
