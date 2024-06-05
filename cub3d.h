/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:09:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 14:27:06 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include "libft/libft.h"

# define H 960
# define W 1600
# define TILE_SIZE 64
# define PLAYER_SIZE 8
# define PI 3.14159265
# define FOV 60
# define CASTED_RAYS 320
# define PL_STEP 20
# define MINIMAP_SCALE 0.2
# define MAX_VAL 100000

/**
 * 
 * 		3Pi/2
 * 		 270
 * 
 *  Pi			0
 * 180			0
 * 				
 * 		Pi/2
 *		 90
 * 
*/

enum e_dir
{
	NO,
	WE,
	SO,
	EA,
};

typedef struct s_parse
{
	int		rows;
	int		cols;
	char	**map;
}	t_parse;

/*!
 *	@struct				s_image
 *	@brief				Represents an image in the MiniLibX graphics library
 *	@param mlx_img		A pointer to the mlx image structure
 *	@param addr			A pointer to the image buffer
 *	@param bpp			The number of bits per pixel
 *	@param line_length	The length of a line in bytes
 *	@param endian		The endian of the image data
 */

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_raycast
{
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;
	float	next_touch_x;
	float	next_touch_y;
	float	wall_hit_x;
	float	wall_hit_y;
	int		found_wall_hit;
	float	hit_dist;
	int		len;
}	t_raycast;

typedef struct s_line
{
	int	x0;
	int	x1;
	int	y_top;
	int	y_botm;
	int	color;
}	t_line;

/**
 * @struct					s_ray
 * @brief					Represents a ray
 * @param	wall_hit_x		X-coordinate of the wall hit
 * @param	wall_hit_y		Y-coordinate of the wall hit
 * @param	size			1 - East, 2 - North, 3 - West, 4 - South

*/

typedef struct s_ray
{
	int		vert_hit;
	float	ray_angle;
	float	distance;
	float	wall_h;
	int		ray_count;
	float	wall_hit_x;
	float	wall_hit_y;
	int		side;
	int		up;
	int		right;
	int		left;
	int		down;
}	t_ray;

/**
 * @struct			s_map
 * @brief			Represents a map with player coordinates and view direction
 * @param	px		X-coordinate of the player in pixels
 * @param	py		Y-coordinate of the player in pixels
 * @param	pa		Angle of the player view's direction
 * @param	pa_rad	Angle of the player view's direction in radians
 * @param	view	Direction the player is facing (N, S, E, W)
 * @param	map		2D array representing the map
*/

typedef struct s_player
{
	float	px;
	float	py;
	float	pa;
	float	pa_rad;
	float	rotation_speed;
}	t_player;

typedef struct s_map
{
	char	*str;
	char	view;
	char	**map;
	int		px;
	int		py;
}	t_map;

typedef struct s_texture
{
	int			width;
	int			height;
	void		*img;
	uint32_t	*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_txr;

/**
 *	@struct		s_elem
 *	@brief		Represents an element with directional information and 
 				color properties
 *	@param so	Represents the direction South
 *	@param no	Represents the direction North
 *	@param ea	Represents the direction East
 *	@param we	Represents the direction West
 *	@param rgb_f	Array representing the foreground color
 *	@param rgb_c	Array representing the ceiling color
 */

typedef struct s_elem
{
	int		rgb_f[3];
	int		rgb_c[3];
	int		hex_f;
	int		hex_c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_txr	*txr[4];
}	t_elem;

/*!
 *	@struct				s_data
 *	@brief				Represents the main data structure containing various
						elements for handling the application state
 *	@param mlx_ptr		A pointer to the main mlx (MiniLibX) structure
 *	@param win_ptr		A pointer to the window structure
 *	@param name			A pointer to the name of the window
 *	@param fd			The file descriptor for file operations
 *	@param arr_file		An array containing lines read from a file
 *	@param rows			The number of rows in the game map
 *	@param lines		The total number of lines read from the file
 *	@param offset		An offset for shifting elements in the array
 *	@param color_buf	A pointer to allocated memory to hold the entire screen
 *	@param img			An instance of the t_image struct representing an image
 *	@param map			A pointer to the t_map struct containing map data
 *	@param elem			A pointer to the t_elem struct containing element data
 */

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*name;
	int			fd;
	char		**arr_file;
	int			rows;
	int			cols;
	int			lines;
	int			offset;
	u_int32_t	*color_buf;
	u_int32_t	*texture_buf;
	t_image		img;
	t_map		*map;
	t_elem		*elem;
	t_ray		*ray;
	t_player	*player;
}	t_data;

/* allowed function:
 open, close, read, write,
 printf, malloc, free, perror,
 strerror, exit
*/

// init data & win
t_data	*initialize_data(void);
void	data_init(t_data *data);
void	window_init(t_data *data);
int		game_map_dup(t_data *data, char **arr);
int		set_color_wall(t_line *line, t_data *data, t_ray *ray);
void	draw_line(t_line *line, t_data *data);
void	draw_vert_line(t_line *line, t_data *data);
void	mini_map(t_data *data);
float	degrees_to_radians(int degrees);
int		get_degree(char view);
int		fix_angle(int a);
void	draw_player_dir(t_data *data, float trgt_x, float trgt_y, float scl);

// read file
int		check_filename(char *str, char *extention);
int		count_file_lines(char *file, t_data	*data);
int		read_file(char *file, t_data	*data);
int		copy_file_content(char *file, t_data *data);
int		validate_player(t_data *data, char **map, int rows);
int		validate_file_content(char *file, t_data *data);
int		parce_file(t_data *data);
int		copy_data(t_data *data, char *s);
int		fill_struct_elem(t_data *data, char **s);
int		copy_texture(t_elem *elem, char **s, char **texture);
int		copy_c_color(t_elem *elem, char **s);
int		copy_f_color(t_elem *elem, char **s);
int		validate_elem(t_elem *elem);

int		cross_exit(t_data *data);
int		keypress(int keysym, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	display_controls(void);
void	move_player(t_data *data, float target_x, float target_y);
void	rotate_player(t_data *data, t_player *player, int keysym);
int		has_wall_at(t_data *data, float x, float y);

//map validation
int		validate_map(char **map, int rows);
int		init_parse_struct(t_parse *data, int rows, char **map);
int		ft_isaplayer(char c);
int		check_for_leaks(t_parse *data, int x, int y, int k);
size_t	get_max_len(char **map);
char	**copy_arr(char **map, int rows);


// draw game
int		game_init(t_data *data);
void	game(t_data *data);
int		load_textures(t_data *data, t_elem *elem);
void	ft_pixel_put(t_image *img, int x, int y, int color);
void	ft_put_pixel_buf(t_data *data, t_image *img);
int		ft_rgb(int r, int g, int b);
void	set_color_ceiling(t_line *line, t_data *data, t_elem *elem);
void	set_color_floor(t_line *line, t_data *data, t_elem *elem);

// raycalsting
void	cast_ray(t_data *data, t_player *player, t_ray *ray);
void	cast_all_rays(t_data *data, t_player *player, t_ray *ray, float scl);
void	update_ray_angle(t_ray *ray);
float	normilize_angle(float angle);
void	init_struct_ray(t_ray *ray, t_player *player);
float	get_distance(float px, float py, float hit_x, float hit_y);
void	render_strip_wall(t_data *data, t_ray *ray);
void	render_3d_walls(t_data *data, t_player *player, t_ray *ray);

// utils
void	print_arr(char **arr);
void	malloc_error(void);
void	clean_up_data(t_data *data);
void	free_elem(t_elem *elem);
void	free_arr_int(int **arr, int size);
int 	free_map_ret_one(t_parse *data, char *msg);
int		print_err(char *s);
size_t	ft_arrlen(char **arr);
size_t	ft_arrsize(char	**arr);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		ft_isspace(int c);
int		ft_isdigit_str(char *s);
void	ft_free(char **str);
void	ft_free_arr(char **arr);
int		count_elem(char *s, char c);
int		get_max_strlen(char **map, int rows);
void	free_texture(t_data *data, t_elem *elem);

#endif