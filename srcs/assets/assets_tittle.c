/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_tittle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:33:59 by kmira             #+#    #+#             */
/*   Updated: 2021/03/31 17:11:22 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			tittle_update(t_animation *self, t_level_context *main_menu)
{
	int					result;

	result = 0;
	(void)self;
	(void)main_menu;
	return (result);
}

t_animation	*tittle_animation(void)
{
	t_animation *tittle;
	int			offset;

	tittle = malloc(sizeof(*tittle));
	tittle->texture = create_texture("resources/ft_png_files/tittle.ft_png");

	offset = tittle->texture->width / 2;

	tittle->texture->screen_pos.coord.x = WIN_WIDTH / 2 - offset;
	tittle->texture->screen_pos.coord.y = WIN_HEIGHT / 2 - 150;
	tittle->update_sprite = tittle_update;

	tittle->next = tittle;

	return (tittle);
}
