/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 03:27:09 by kmira             #+#    #+#             */
/*   Updated: 2020/03/07 20:21:05 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_texture(t_texture *texture, t_wolf_window *mgr_wolf_window)
{
	int		row;
	int		col;
	t_color	color;

	row = 0;
	while (row < texture->height)
	{
		col = 0;
		while (col < texture->width)
		{
			if (texture->memory_array[row * texture->width * BPP + col * BPP + 3] >= 20)
			{
				color.col_32bit = *(int *)(&texture->memory_array[row * texture->width * BPP + col * BPP]);
				push_pixel(texture->screen_pos.coord.x + col,
							texture->screen_pos.coord.y + row,
							color, mgr_wolf_window->pixel_array);
			}
			col++;
		}
		row++;
	}
}

/*
**          (y)|        /(z)
**             |      /
**             |    /
**             |  /
**   __________|/_________ (x)
**            /|
**          /  |
**        /    |
**      /      |
**
** y-axis = world height; window height
** x-axis = world width ; window width
** z-axis = world depth
*/

void	render2_texture(t_texture *texture, t_wolf_window *window, t_player *player, char **map)
{
	printf("PLAYER_ANGLE: %f\n", player->angle);
	printf("PLAYER: (%f, %f)\n", player->pos.coord.x, player->pos.coord.y);

	move_cursor_up(14);

	(void)texture;
	(void)window;
	(void)player;
	(void)map;
	return ;
}

// https://www.geogebra.org/3d/rfkkvfuq
