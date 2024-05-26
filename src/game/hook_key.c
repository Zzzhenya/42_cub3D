/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:16 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 21:12:40 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cross(data);
	if (keysym == XK_Left || keysym == XK_Right)
		return (rotate_player(data, data->player, keysym), 0);
	if (keysym == XK_w || keysym == XK_W)
	{
		move_player(data, (data->player->px + cos(data->player->pa_rad) * PL_STEP),\
		(data->player->py + sin(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_s || keysym == XK_S)
	{
		move_player(data, (data->player->px - cos(data->player->pa_rad) * PL_STEP),\
		(data->player->py - sin(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_a || keysym == XK_A)
	{
		move_player(data, (data->player->px + sin(data->player->pa_rad) * PL_STEP),\
		(data->player->py - cos(data->player->pa_rad) * PL_STEP));
	}
	else if (keysym == XK_d || keysym == XK_D)
	{
		move_player(data, (data->player->px - sin(data->player->pa_rad) * PL_STEP),\
		(data->player->py + cos(data->player->pa_rad) * PL_STEP));
	}
	return (game(data), 0);
}

void	move_player(t_data *data, float target_x, float target_y)
{
	int	check_x;
	int	check_y;

	if (target_x < 0 || target_x > W || target_y < 0 || target_y > H)
		return ;
	check_x = (int)floor(target_x / CELLSIZE);
	check_y = (int)floor(target_y / CELLSIZE);
	// printf("px:%f, py:%f\n", data->player->px, data->player->py); //rm
	// printf("check_x: %d, check_y: %d\n", check_x, check_y); //rm
	// printf("new_x: %f, new_y: %f\n", target_x, target_y); //rm
	if (data->map->map[(int)floor(data->player->py / CELLSIZE)][check_x] != '1')
		data->player->px = target_x;
	if (data->map->map[check_y][(int)floor(data->player->px / CELLSIZE)] != '1')
		data->player->py = target_y;
}

void	rotate_player(t_data *data, t_player *player, int keysym)
{
	if (keysym == XK_Left)
	{
		printf("data->player->pa_rad: %f, +0.05: %f\n", player->pa_rad, player->pa_rad + 0.05);
		player->pa_rad += player->rotation_speed;
		if (player->pa_rad > 2 * PI)
			player->pa_rad -= 2 * PI;
	}
	else if (keysym == XK_Right)
	{
		player->pa_rad -= player->rotation_speed; //0.05
		if (player->pa_rad < 0)
			player->pa_rad += 2 * PI;
	}
	game(data);
}


int	cross(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	clean_up_data(data);
	exit (EXIT_SUCCESS);
}
