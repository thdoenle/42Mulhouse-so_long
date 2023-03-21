/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:20:30 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 17:47:21 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

typedef enum e_move_type
{
	MOVE_SPAWN = 0,
	MOVE_DEATH,
	MOVE_WIN,
	MOVE_IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
}	t_move_type;

typedef struct s_lst
{
	int				l;
	int				c;
	int				x;
	int				y;
	bool			draw;
	struct s_lst	*next;
}	t_lst;

typedef struct s_coords
{
	int		l;
	int		c;
	int		x;
	int		y;
	int		move;
	double	t;
	int		x_from;
	int		y_from;
	int		x_to;
	int		y_to;
}	t_coords;

typedef struct s_move
{
	int				x_from;
	int				y_from;
	int				x_to;
	int				y_to;
	int				dir;
	double			time;
	struct s_move	*next;
}	t_move;

typedef struct s_track
{
	t_move	*oldest;
	t_move	*newest;
}	t_track;

typedef struct s_foe
{
	int				x;
	int				y;
	double			t;
	t_move			*move_ptr;
	t_move_type		move_type;
	mlx_image_t		*img;
	struct s_foe	*next;
}	t_foe;

typedef struct s_image_area
{
	mlx_image_t	*img;
	uint32_t	x;
	uint32_t	y;
	uint32_t	w;
	uint32_t	h;
}	t_img_area;

typedef struct s_anim
{
	mlx_image_t	**img;
	double		nb_img;
	double		t;
	double		t_max;
}	t_anim;

void		ft_putchar(char c);
void		ft_putnbr(unsigned int n);
void		ft_putstr_fd(int fd, char *s);
int			ft_strlen(char *s);
void		ft_strcpy(char *dest, char *src);
void		ft_bzero(void *addr, size_t len);
void		ft_pixelset(void *addr, uint32_t val, size_t len);
char		**str_tab_copy(char **tab);

t_lst		*lstnew(int l, int c, int x, int y);
void		lstadd_front(t_lst **lst, t_lst *new);
t_lst		*lstget(t_lst *lst, int l, int c);
void		lstclear(t_lst **lst);

t_foe		*foenew(t_move *move_ptr);
void		foeadd_front(t_foe **foes, t_foe *new);
void		foesclear(t_foe **foes);

t_move		*movenew(t_coords *coords, t_move_type dir);
void		movesclear(t_move **moves);

t_anim		get_anim(mlx_t *mlx, const char *path, int nb_img, double time);
t_anim		get_rev_anim_copy(t_anim anim);

mlx_image_t	*new_placeholder(mlx_t *mlx, uint32_t len, uint32_t color);
mlx_image_t	*texture_to_image_resized(mlx_t *mlx, mlx_texture_t *t,
				uint32_t scale);
mlx_image_t	*get_image_from_png(mlx_t *mlx, const char *path, uint32_t size);
void		draw_image(mlx_image_t *dest, mlx_image_t *src, uint32_t x,
				uint32_t y);
void		draw_image_from_coords(mlx_image_t *dest, mlx_image_t *src,
				uint32_t x, uint32_t y);
void		draw_image_from_image_area(mlx_image_t *dest, t_img_area *src,
				uint32_t x, uint32_t y);

#endif
