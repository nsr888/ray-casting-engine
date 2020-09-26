/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:02:38 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/20 17:44:28 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <fcntl.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "struct.h"

/*
** cub3d.c
*/

void	exit_error(int e);

/*
** cub3d_utils.c
*/

int		ft_isspace(int c);

/*
** parser.c
*/

t_map	*parser(char *filename);

/*
** parser_switch.c
*/

void	parser_switch(char *s, t_map *map, int i);

/*
** parser_map_init.c
*/

void	map_init_and_allocate(t_list *lst, t_map *map);

/*
** map_fill_content.c
*/

void	map_fill_content(t_list *lst, t_map *map, unsigned int col, \
		unsigned int row);

/*
** check_map.c
*/

int		check_map(t_map *map);

/*
** game_loop.c
*/

void	game_loop(t_map *map);

/*
** game_loop_update.c
*/

int		render_next_frame(t_vars *vars);
void	update(t_vars *vars);

/*
** game_loop_update2.c
*/

int		is_wall(t_vars *vars, double x, double y);
void	change_player_coord(t_vars *vars);

/*
** raycasting.c
*/

t_rays	**cast_all_rays(t_vars *vars);

/*
** raycasting_hit_horizontal.c
*/
void	get_distance_h(t_vars *vars, t_point *plr, double angle, \
		t_rays *ray_h);

/*
** raycasting_hit_vertical.c
*/

void	get_distance_v(t_vars *vars, t_point *plr, double angle, \
		t_rays *ray_v);

/*
** raycasting_utils.c
*/

int		is_ray_down(double angle);
int		is_ray_right(double angle);
double	norm_angle(double angle);
double	calc_dist(double x1, double y1, double x2, double y2);

/*
** render3d.c
*/

void	render3d(t_vars *vars, t_rays **rays, int i);
int		add_shade(double distance, int color);

/*
** render3d_colors.c
*/

int		get_color_sprite(t_data img, t_rect r, int k, int j);
int		get_color(t_data *img, t_rays *rays, t_rect *r, int j);
double	calc_shade(double distance, t_vars *vars);
void	set_color_from_wall(t_rays *rays, t_vars *vars, t_rect *r, int j);

/*
** color.c
*/

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_b(int trgb);
int		get_g(int trgb);
int		get_r(int trgb);

/*
** events.c
*/

int		key_p(int keycode, t_vars *vars);
int		key_r(int keycode, t_vars *vars);
int		window_close(void);

/*
** draw_minimap.c
*/

void	draw_line(t_data *img, t_rect p0, t_rect p1);
void	draw_map(char **content, t_vars *vars);
void	draw_minimap_rays(t_vars *vars, t_rays **rays);

/*
** draw_minimap_utils.c
*/

void	draw_rect(t_rect *rect, t_data *img);
void	draw_square_from_center(t_rect r, t_data *img);
void	draw_square(t_rect r, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*
** draw_sprites.c
*/

void	draw_sprites(t_vars *vars, t_rays **rays);

/*
** draw_sprites_render.c
*/

void	render_sprites(t_vars *vars, t_rays **rays);

/*
** writebmp.c
*/

void	save_bmp(t_data img, int w, int h, int x);

#endif
