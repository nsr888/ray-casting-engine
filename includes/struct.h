/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:02:38 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/15 15:59:15 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define MAP_SCALE 64
# define WALK_SPD 16.43
# define ROTATION_SPEED (6 * (M_PI / 180))
# define FOV_ANGLE M_PI / 3
# define WALL_STRIP_WIDTH 1
# define MINIMAP_SCALE 0.1

typedef struct		s_data {
	char			*path;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_data;

typedef struct		s_rays {
	int				was_hit_vertical;
	double			angle;
	double			distance;
	char			wall_type;
	double			wall_hit_x;
	double			wall_hit_y;
}					t_rays;

typedef	struct		s_point {
	double			x;
	double			y;
	int				turn_direction;
	int				walk_direction;
	int				strafe;
	double			angle;
	int				num_rays;
}					t_point;

typedef struct		s_sprites {
	double			x;
	double			y;
	double			distance;
	double			angle;
	double			size;
}					t_sprites;

typedef struct		s_map {
	int				w;
	int				h;
	unsigned int	rows;
	unsigned int	cols;
	t_data			no;
	t_data			so;
	t_data			we;
	t_data			ea;
	t_data			s;
	int				f;
	int				c;
	char			save_bmp;
	char			**content;
	int				sprites_num;
	t_sprites		*sprites;
	t_point			player;
}					t_map;

typedef struct		s_vars {
	void			*mlx;
	void			*win;
	time_t			key_time;
	char			key;
	t_data			img;
	t_map			*map;
}					t_vars;

typedef	struct		s_rect {
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_rect;

#endif
