/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:16 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 18:28:18 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cross_exit(data);
	if (keysym == XK_Left || keysym == XK_Right)
		return (rotate_player(data, data->player, keysym), 0);
	if (keysym == XK_w || keysym == XK_W)
	{
		move_player(data, (data->player->px + cos(data->player->pa_rad) * \
		PL_STEP), (data->player->py + sin(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_s || keysym == XK_S)
	{
		move_player(data, (data->player->px - cos(data->player->pa_rad) * \
		PL_STEP), (data->player->py - sin(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_a || keysym == XK_A)
	{
		move_player(data, (data->player->px + sin(data->player->pa_rad) * \
		PL_STEP), (data->player->py - cos(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_d || keysym == XK_D)
	{
		move_player(data, (data->player->px - sin(data->player->pa_rad) * \
		PL_STEP), (data->player->py + cos(data->player->pa_rad) * PL_STEP));
	}
	return (game(data), 0);
}

void	move_player(t_data *data, float target_x, float target_y)
{
	if (has_wall_at(data, target_x, data->player->py) != 1)
		data->player->px = target_x;
	if (has_wall_at(data, data->player->px, target_y) != 1)
		data->player->py = target_y;
}

void	rotate_player(t_data *data, t_player *player, int keysym)
{
	if (keysym == XK_Left)
		player->pa_rad -= player->rotation_speed;
	else if (keysym == XK_Right)
		player->pa_rad += player->rotation_speed;
	game(data);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)data;
	printf("Mouse is at position (%d, %d)\n", x, y);
	return (0);
}

int	cross_exit(t_data *data)
{
	free_texture(data, data->elem);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	clean_up_data(data);
	exit (EXIT_SUCCESS);
}
