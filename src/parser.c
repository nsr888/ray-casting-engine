/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:18:31 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/20 17:48:41 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_map	*lst_to_map(t_list *lst, int i)
{
	t_map	*map;
	char	*s;

	if (!(map = ft_calloc(1, sizeof(*map))))
		exit_error(3);
	while (lst)
	{
		s = lst->content;
		i = 0;
		if (ft_isalpha(s[i]))
			parser_switch(s, map, i);
		else if (s[i] == ' ' || s[i] == '1')
		{
			map_init_and_allocate(lst, map);
			map_fill_content(lst, map, 0, 0);
			if (map->content == NULL)
				exit_error(4);
			break ;
		}
		else if (s[i] != '\0')
			exit_error(4);
		lst = lst->next;
	}
	return (map);
}

t_map			*parser(char *filename)
{
	t_list	*lst;
	t_map	*map;
	int		fd;
	char	*line;

	lst = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit_error(8);
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	ft_lstadd_back(&lst, ft_lstnew(line));
	if (!(map = lst_to_map(lst, 0)))
		return (NULL);
	ft_lstclear(&lst, free);
	return (map);
}
