/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writebmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:01:31 by ksinistr          #+#    #+#             */
/*   Updated: 2020/09/15 20:10:24 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void						write_image_data(int fd, unsigned int w, \
							unsigned int h, unsigned char *img)
{
	static unsigned char	bmppad[3] = {0, 0, 0};
	unsigned int			i;

	i = 0;
	while (i < h)
	{
		if (write(fd, img + (w * (h - i - 1) * 3), 3 * w) < 0)
			exit_error(9);
		if (write(fd, bmppad, (4 - (w * 3) % 4) % 4) < 0)
			exit_error(9);
		i++;
	}
}

void						write_bmp(char *filename, unsigned int w, \
							unsigned int h, unsigned char *img)
{
	int						fd;
	unsigned int			*size_of_file_entry;
	unsigned int			*width_entry;
	unsigned int			*height_entry;
	static unsigned char	header[54] = {66, 77, 0, 0, 0, 0, 0, 0, 0, 0, 54, \
		0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24};

	size_of_file_entry = (unsigned int*)&header[2];
	*size_of_file_entry = 54 + 3 * w * h;
	width_entry = (unsigned int*)&header[18];
	*width_entry = w;
	height_entry = (unsigned int*)&header[22];
	*height_entry = h;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | \
			S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (write(fd, header, 54) < 0)
		exit_error(9);
	write_image_data(fd, w, h, img);
	close(fd);
}

void						save_bmp(t_data img, int w, int h, int x)
{
	int						c[3];
	int						y;
	unsigned char			*pixels;

	if (!(pixels = ft_calloc(w, 3 * h)))
		exit_error(3);
	while (x < w)
	{
		y = -1;
		while (++y < h)
		{
			c[0] = img.addr[(y * img.line_length + \
				x * (img.bits_per_pixel / 8) + 0)] & 0x000000FF;
			c[1] = img.addr[(y * img.line_length + \
				x * (img.bits_per_pixel / 8) + 1)] & 0x000000FF;
			c[2] = img.addr[(y * img.line_length + \
				x * (img.bits_per_pixel / 8) + 2)] & 0x000000FF;
			pixels[(x + y * w) * 3 + 2] = (unsigned char)(c[2]);
			pixels[(x + y * w) * 3 + 1] = (unsigned char)(c[1]);
			pixels[(x + y * w) * 3 + 0] = (unsigned char)(c[0]);
		}
		x++;
	}
	write_bmp("screenshot.bmp", w, h, pixels);
	free(pixels);
}
