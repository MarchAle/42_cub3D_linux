SRC =	main.c					\
			parse_map.c 			\
			parse_file.c			\
			build_map.c				\
			get_params.c 			\
			game.c					\
			init_struct.c			\
			init_texture.c			\
			print_view.c			\
			moves.c					\
			acceleration.c			\
			collision.c				\
			collision_monster.c		\
			raycasting.c 			\
			key_hook.c				\
			dist_to_wall.c			\
			dist_to_wall_utils.c	\
			render_img.c			\
			render_wall.c 			\
			render_sky.c 			\
			render_floor.c 			\
			minimap.c 				\
			color.c 				\
			error.c 				\
			utils.c 				\
			list_utils.c			\
			render_sprites.c		\
			calcul.c				\
			monster.c				\
			doors.c					\

NAME = Cub3D

LIB := ./libft/libft.a
LIBMLX = ./mlx_linux/libmlx.a
MLX_DIR = mlx_linux
MLX = libmlx.a 
CC = clang

# diff entre .a et .dylib
# .a = lib static, les fonctions utilisees sont directement ecrite dans le binaire
# .dylib = lib dynamique, les fonctions doivent etre chargees au momnent ou on lance le binaire

CFLAGS = -pthread -Wall -Wextra -Werror -O3 -g #-pg #-fsanitize=address
CFRAM := -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

OBJ_DIR = objs
SRC_DIR = srcs
INC_DIR = includes

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

# -C faire make comme si on etait dana le dossier
# -j multisreder / ameliore la vitesse de compliation
# Pas de regle opti car makefile mlx pas compatible
all:
	@$(MAKE) -j $(NAME)
	@echo "\033[0;32mProject is ready !\033[0m"

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
# -L donner le nom du dossier / -l donner le nom le la lib
# loader path = ecrit le chemin de la mlx dans le binaire pour pouvoir la retrouver au moment ou on lance le binaire
$(NAME): $(LIBMLX) $(LIB) $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) $(LIBMLX) $(LIB) -L $(MLX_DIR) $(CFRAM)
		@echo "\033[0;32mCompilation succeed !\033[0m"

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
	@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

# Utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)
