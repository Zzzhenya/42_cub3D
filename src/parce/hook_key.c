/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:16 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/09 19:33:55 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cross(data);
	else if (keysym == XK_w || keysym == XK_W)
		data->map->py += 5;
	else if (keysym == XK_a || keysym == XK_A)
		data->map->px -= 5;
	else if (keysym == XK_s || keysym == XK_S)
		data->map->py += 5;
	else if (keysym == XK_d || keysym == XK_D)
		data->map->px += 5;
	else if (keysym == XK_Left)
		write(1, "Left\n", 5);
	else if (keysym == XK_Right)
		write(1, "Right\n", 6);
	return (0);
}

int	cross(t_data *data)
{
	// mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (EXIT_SUCCESS);
}

// int	mouse(int button, int x, int y, t_data *data)
// {
// 	(void)x;
// 	(void)y;
// 	(void)data;
// 	(void)button;
// 	printf("%i %i\n", x, y);
// 	// if (button == Button5)
// 	// {
// 	// 	fractal->zoom *= 0.95;
// 	// }
// 	// else if (button == Button4)
// 	// {
// 	// 	fractal->zoom *= 1.05;
// 	// }
// 	// draw_fractal(fractal);
// 	return (0);
// }
