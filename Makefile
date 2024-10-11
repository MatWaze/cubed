NAME = cub3D
BUILD_DIR = build
mlx_dir = minilibx
libft_dir = libft
lflags = -L$(libft_dir) -L$(mlx_dir)
iflags = -I. -I/usr/include
cflags = -Wall -Wextra -Werror -g

all : make_dirs $(NAME)

debug: cflags += -g
debug: all

sanitize : cflags += -g -fsanitize=address -fsanitize=undefined
sanitize : lflags += -fsanitize=address -fsanitize=undefined
sanitize : all

#         ____   __   ____  ____  __  __ _   ___
#        (  _ \ / _\ (  _ \/ ___)(  )(  ( \ / __)
#         ) __//    \ )   /\___ \ )( /    /( (_ \
#        (__)  \_/\_/(__\_)(____/(__)\_)__) \___/

parsing_dir = $(BUILD_DIR)/parsing
parsing_modules = validation check_characters texture_parsing valid_texture valid_map get_map door_check
obj += $(addprefix $(parsing_dir)/, $(addsuffix .o, $(parsing_modules)))
$(parsing_dir): | $(BUILD_DIR)
	mkdir $@

#          ___  __   _  _  _  _   __   __ _
#         / __)/  \ ( \/ )( \/ ) /  \ (  ( \
#        ( (__(  O )/ \/ \/ \/ \(  O )/    /
#         \___)\__/ \_)(_/\_)(_/ \__/ \_)__)

common_dir=$(BUILD_DIR)/common
common_modules= common matrix
obj += $(addprefix $(common_dir)/, $(addsuffix .o, $(common_modules)))
$(common_dir): | $(BUILD_DIR)
	mkdir $@

#         ____  ____  ____   __  ____
#        (  __)(  _ \(  _ \ /  \(  _ \
#         ) _)  )   / )   /(  O ))   /
#        (____)(__\_)(__\_) \__/(__\_)

error_dir=$(BUILD_DIR)/error
error_modules = error trace
obj += $(addprefix $(error_dir)/, $(addsuffix .o, $(error_modules)))
$(error_dir): | $(BUILD_DIR)
	mkdir $@

#          ___  ____  ____        _  _   __  ____  _  _
#         / __)( __ \(    \      ( \/ ) / _\(_  _)/ )( \
#        ( (__  (__ ( ) D ( ____ / \/ \/    \ )(  ) __ (
#         \___)(____/(____/(____)\_)(_/\_/\_/(__) \_)(_/

c3d_math_dir=$(BUILD_DIR)/c3d_math
c3d_math_modules = create distances set vec_op
obj += $(addprefix $(c3d_math_dir)/, $(addsuffix .o, $(c3d_math_modules)))
$(c3d_math_dir): | $(BUILD_DIR)
	mkdir $@

#          ___    __    __  __  ____
#         / __)  /__\  (  \/  )( ___)
#        ( (_-. /(__)\  )    (  )__)
#         \___/(__)(__)(_/\/\_)(____)

game_dir=$(BUILD_DIR)/game
game_modules=hooks render image minimap
obj += $(addprefix $(game_dir)/, $(addsuffix .o, $(game_modules)))
$(game_dir): | $(BUILD_DIR)
	mkdir $@

#         ____    __   _  _  ___    __    ___  ____
#        (  _ \  /__\ ( \/ )/ __)  /__\  / __)(_  _)
#         )   / /(__)\ \  /( (__  /(__)\ \__ \  )(
#        (_)\_)(__)(__)(__) \___)(__)(__)(___/ (__)

raycast_dir=$(BUILD_DIR)/raycast
raycast_modules=raycast raycast_direct cross
obj += $(addprefix $(raycast_dir)/, $(addsuffix .o, $(raycast_modules)))
$(raycast_dir): | $(BUILD_DIR)
	mkdir $@

obj += $(BUILD_DIR)/cub3D.o

depflags = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

$(NAME): $(mlx_dir)/libmlx.a $(libft_dir)/libft.a $(obj)
	cc $(lflags) $(cflags) -o $@ $(obj) -lmlx -lft -framework OpenGL -framework AppKit

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)/%.d Makefile
	cc $(cflags) $(iflags) $(depflags) -c $< -o $@

clean : $(mlx_dir)/Makefile
	rm -rf $(BUILD_DIR)
	make -C $(libft_dir) clean
	make -C $(mlx_dir) clean

fclean: clean
	make -C $(libft_dir) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_dirs

make_dirs: $(parsing_dir) $(common_dir) $(error_dir) $(c3d_math_dir) $(game_dir) $(raycast_dir)

$(libft_dir)/libft.a:
	make -C $(libft_dir)

$(mlx_dir)/libmlx.a:
	make -C $(mlx_dir)

$(BUILD_DIR):
	mkdir $@

$(obj:.o=.d):
include $(obj:.o=.d)

test: Makefile texture_resizing_test.c
	cc $(cflags) texture_resizing_test.c -o $@ $(lflags) -lmlx -framework OpenGL -framework AppKit
