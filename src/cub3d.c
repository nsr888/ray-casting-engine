/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:36:00 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/16 15:34:53 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			exit_error(int e)
{
	ft_putstr_fd("Error\n", 2);
	if (e == 1)
		ft_putstr_fd("Too many arguments\n", 2);
	else if (e == 3)
		ft_putstr_fd("Can't allocate memory via malloc\n", 2);
	else if (e == 4)
		ft_putstr_fd("Wrong .cub file format\n", 2);
	else if (e == 5)
		ft_putstr_fd("Wrong file extension of first argument\n", 2);
	else if (e == 6)
		ft_putstr_fd("usage: cub3D file.cub [--save]\n", 2);
	else if (e == 7)
		ft_putstr_fd("Second argument is incorrect\n", 2);
	else if (e == 8)
		ft_putstr_fd("No such file\n", 2);
	else if (e == 9)
		ft_putstr_fd("Write error\n", 2);
	else if (e == 10)
		ft_putstr_fd("Texture error\n", 2);
	exit(0);
}

static int		is_filename_correct(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!(ext))
		return (0);
	if (ft_strncmp(ext, ".cub", 5))
		return (0);
	return (1);
}

int				main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 1)
		exit_error(6);
	if (argc > 3)
		exit_error(1);
	if (!is_filename_correct(argv[1]))
		exit_error(5);
	if (!(map = parser(argv[1])))
		exit_error(4);
	if (!check_map(map))
		exit_error(4);
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) == 6 && !ft_strncmp(argv[2], "--save", 7))
			map->save_bmp = 1;
		else
			exit_error(7);
	}
	game_loop(map);
	return (0);
}
