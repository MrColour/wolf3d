/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:57:44 by kmira             #+#    #+#             */
/*   Updated: 2020/03/08 10:38:39 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCTS_H
# define WOLF_STRUCTS_H

# include "glfw3.h"

# include <stdlib.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 512

typedef struct	s_level_context t_level_context;

/*
** The union has its bits in a certain order, do not change
** unless you know what you are doing and are on a machine
** thats ENDIANNESS is different from MacOs.
*/

typedef union	u_color
{
	uint32_t	col_32bit;
	uint8_t		col_8bit[4];
	struct
	{
		uint8_t	blue;
		uint8_t	green;
		uint8_t	red;
		uint8_t	alpha;
	}			channel;
}				t_color;

# define X 0
# define Y 1
# define Z 2

typedef union	u_vector3i
{
	int			vector[3];
	struct
	{
		int		x;
		int		y;
		int		z;
	}			coord;
}				t_vector3i;

typedef union	u_vector3f
{
	double		vector[3];
	struct
	{
		double		x;
		double		y;
		double		z;
	}			coord;
}				t_vector3f;

/*
** This is a transformation matrix.
** Just like in arrays the memory mapping is (y, x).
** But in code we can make the api Cartesian.
*/

typedef union	u_matrix_3i
{
	double		matrix[3][3];
}				t_matrix3i;

typedef struct	s_texture
{
	uint8_t		*memory_array;
	int			width;
	int			height;
	t_vector3i	world_pos;
	t_vector3i	screen_pos;
	t_matrix3i	transform;
}				t_texture;

typedef struct	s_animation
{
	int					tick_change;
	int					*individual_lock;
	int					*shared_lock;
	t_texture			*texture;
	struct s_animation	*next;

	int					(*update_sprite)(struct s_animation *self, t_level_context *level);
}				t_animation;

typedef	struct	s_wolf_window
{
	GLFWwindow	*window;
	uint8_t		**pixel_array;
	int			bpp;

	t_color		background_color;
}				t_wolf_window;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

//0 = up, 1 = down, 2 = left, 3 = right
typedef struct s_rayhit
{
	t_vector3f	pos;
	int			side;
}				t_rayhit;

typedef struct	s_ray
{
	t_vector3f	vect;
	t_rayhit	hit;
	char		hits[WIN_WIDTH];
}				t_ray;

typedef struct	s_player
{
	double		angle;
	t_vector3f	pos;
	t_vector3f	dir;
}				t_player;

#endif
