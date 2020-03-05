/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_first_level.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:45:33 by kmira             #+#    #+#             */
/*   Updated: 2020/03/04 22:57:56 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_level_context	*first_level(t_wolf_window *mgr_wolf_window)
{
	t_level_context	*result;
	t_level_first	*self_full;

	self_full = malloc(sizeof(*self_full));
	ft_bzero(self_full, sizeof(*self_full));
	self_full->common_level.init_self = level_init_first_level;
	self_full->common_level.mgr_wolf_window = mgr_wolf_window;

	result = (t_level_context *)self_full;
	return (result);
}

int				level_init_first_level(t_level_context *level, t_wolf_window *mgr_wolf_window)
{
	t_level_first	*self_full;

	self_full = (t_level_first *)level;

	self_full->common_level.mgr_wolf_window = mgr_wolf_window;
	self_full->common_level.run_level = level_loop_first_level;
	self_full->common_level.is_running = level_running_first_level;
	self_full->common_level.get_input = level_get_input_first_level;
	self_full->common_level.get_next_level = level_get_next_first_level;
	self_full->common_level.clean_level = level_clean_first_level;

	self_full->map = get_map("map00");
	player_init(&self_full->player, self_full->map);

	self_full->common_level.level_ticks = 0;

	self_full->animation_array = malloc(sizeof(*self_full->animation_array) * (3 + 1));

	mgr_wolf_window->background_color.col_32bit = 0x777777;
	return (1);
}

void			level_get_input_first_level(t_level_context *self)
{
	t_level_first	*level;
	t_wolf_window	*wolf_window;

	glfwPollEvents();
	level = (t_level_first *)self;
	wolf_window = level->common_level.mgr_wolf_window;
	if (glfwGetKey(wolf_window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wolf_window->window, GL_TRUE);
		game_running(GAME_STATE_SET, SHUTDOWN_GAME);
		level->h_game_state = 'e';
	}
	else if (glfwGetKey(wolf_window->window, GLFW_KEY_D) == GLFW_PRESS && level->h_toggle == 0)
	{
		level->h_toggle = 1;
		level->player.posx += 1;
		self->level_ticks = 15;
	}
	else if (glfwGetKey(wolf_window->window, GLFW_KEY_A) == GLFW_PRESS && level->h_toggle == 0)
	{
		level->h_toggle = 1;
		level->player.posx -= 1;
		self->level_ticks = 15;
	}
	else if (glfwGetKey(wolf_window->window, GLFW_KEY_W) == GLFW_PRESS && level->h_toggle == 0)
	{
		level->h_toggle = 1;
		level->player.posy -= 1;
		self->level_ticks = 15;
	}
	else if (glfwGetKey(wolf_window->window, GLFW_KEY_S) == GLFW_PRESS && level->h_toggle == 0)
	{
		level->h_toggle = 1;
		level->player.posy += 1;
		self->level_ticks = 15;
	}
}

int				level_running_first_level(t_level_context *self)
{
	int				result;
	t_level_first	*self_full;

	result = 1;
	self_full = (t_level_first *)self;
	if (glfwWindowShouldClose(self->mgr_wolf_window->window))
		result = 0;
	else if (self_full->h_game_state == 'e')
		result = 0;
	else if (self_full->h_game_state == '\007')
		result = 0;
	return (result);
}

t_level_context	*level_loop_first_level(t_level_context *self)
{
	t_wolf_window	*mgr_wolf_window;
	t_level_context	*new_level;
	t_level_first	*self_full;

	self_full = (t_level_first *)self;
	mgr_wolf_window = self->mgr_wolf_window;
	while (self->is_running(self))
	{
		self->get_input(self);

		if (self_full->h_toggle == 1 && self->level_ticks % 25 == 0)
		{
			printf("PLAYER POS (%3d, %3d)\n", self_full->player.posx, self_full->player.posy);
			// print_map(self_full->map);
			self_full->h_toggle = 0;
			self->level_ticks = 0;
		}

		refresh_screen(mgr_wolf_window);
		self->level_ticks++;
	}
	new_level = self->get_next_level(self);
	self->clean_level(self);
	return (new_level);
}

t_level_context	*level_get_next_first_level(struct s_level_context *self)
{
	(void)self;
	return (NULL);
}

int		level_clean_first_level(t_level_context *self)
{
	(void)self;
	return (42);
}