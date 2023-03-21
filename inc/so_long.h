/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:44:47 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/18 18:34:42 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42.h"
# include "get_next_line.h"
# include "lib.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define ERR -1

# define TIME_MOVE 0.12
# define TIME_DIE 0.5
# define TIME_KEY 1.
# define TIME_FOE_SPAWN 1.1

typedef enum e_len
{
	LEN_SCREEN = 1024,
	LEN_TILE = 64,
	LEN_PIXEL = 4
}	t_len;

typedef struct s_bg_images
{
	mlx_image_t	*layer;
	mlx_image_t	*bg;
	mlx_image_t	*wall_tl;
	mlx_image_t	*wall_e;
	mlx_image_t	*wall_bl;
	mlx_image_t	*wall_s;
	mlx_image_t	*wall_n;
	mlx_image_t	*wall_tr;
	mlx_image_t	*wall_w;
	mlx_image_t	*wall_br;
	mlx_image_t	*wall_ne;
	mlx_image_t	*wall_nw;
	mlx_image_t	*wall_nwe;
	mlx_image_t	*wall;
	mlx_image_t	*wall_h;
	mlx_image_t	*floor;
	mlx_image_t	*floor_n;
	mlx_image_t	*floor_s;
	mlx_image_t	*floor_e;
	mlx_image_t	*floor_w;
	mlx_image_t	*floor_nw;
	mlx_image_t	*floor_ne;
	mlx_image_t	*floor_ns;
	mlx_image_t	*floor_sw;
	mlx_image_t	*floor_se;
	mlx_image_t	*floor_we;
	mlx_image_t	*floor_nsw;
	mlx_image_t	*floor_nse;
	mlx_image_t	*floor_nwe;
	mlx_image_t	*floor_swe;
	mlx_image_t	*floor_nswe;
}	t_bg_images;

typedef struct s_images
{
	t_bg_images	bg;
	mlx_image_t	*main_layer;
	mlx_image_t	*win_layer;
	mlx_image_t	*player_d;
	mlx_image_t	*player_u;
	mlx_image_t	*player_l;
	mlx_image_t	*player_r;
	mlx_image_t	*foe_d;
	mlx_image_t	*foe_u;
	mlx_image_t	*foe_l;
	mlx_image_t	*foe_r;
	mlx_image_t	*exit;
	mlx_image_t	*exit_o;
	mlx_image_t	*font;
}	t_images;

typedef struct s_anims
{
	t_anim	col;
	t_anim	p_death;
	t_anim	p_spawn;
	t_anim	foe_death;
	t_anim	foe_spawn;
}	t_anims;

typedef struct s_data
{
	mlx_t		*mlx;
	char		**map;
	int			map_w;
	int			map_h;
	int			max_col;
	int			nb_col;
	int			nb_mv;
	int			fps;
	double		timer;
	int			p_l;
	int			p_c;
	t_move_type	dir;
	double		p_h;
	double		foe_delay;
	t_coords	*p;
	t_foe		*foes;
	t_track		*tracks;
	t_lst		*c;
	t_coords	*e;
	bool		win;
	int			o_x;
	int			o_y;
	int			map_o_x;
	int			map_o_y;
	t_images	*img;
	t_anims		*anim;
}	t_data;

typedef struct s_flood
{
	char	**map;
	int		exit;
	int		nb_col;
}	t_flood;

void		free_data(t_data *data);
void		free_map(char **map);
void		error(char *msg);
void		abort_parsing(t_data *data, void *to_free, int fd, char *msg);
void		abort_game(t_data *data);

void		parse_map(t_data *data, char *file);
int			check_file_ext(char *file, char *ext);
int			count_lines(char *file);
void		store_map(t_data *data, char *file);
void		set_player_coords(t_data *data, int l, int c);
void		set_exit_coords(t_data *data, int l, int c);
void		add_collectible(t_data *data, int l, int c);
void		set_map_offset(t_data *data);

void		closefunc(void *param);
void		keyfunc(mlx_key_data_t keydata, void *param);
void		loopfunc(void *param);

void		start_game(t_data *data);
void		init_tracks(t_data *data);
void		init_images(t_data *data);
void		init_animations(t_data *data);
void		init_background(t_data *data);
mlx_image_t	*which_image_to_draw_at_tile(t_data *data, int c, int l);
mlx_image_t	*which_floor_to_draw_at_tile(t_data *data, int l, int c);
bool		is_wall(t_data *data, int l, int c);
void		restart_game(t_data *data);

void		update(t_data *data);
void		update_positions(t_data *data);
void		calc_offset(t_data *data);
void		update_player_pos(t_data *data);
void		tracks_update_current_move(t_data *data);
void		update_foes(t_data *data);
void		update_animations(t_data *data);
void		update_hud(t_data *data);
void		put_str_to_image(t_data *data, mlx_image_t *dst, char *msg,
				uint32_t *xy_nums);
uint32_t	strtoimage_len(char *s, uint32_t *nums);
mlx_image_t	*get_anim_img(t_anim *anim);

void		draw_player(t_data *data);
void		draw_foes(t_data *data);

void		tracks_add_move(t_data *data);
void		tracks_rm_oldest_move(t_data *data);
void		add_foe(t_data *data);

bool		is_player_colliding_with_foe(t_data *data);

#endif
