name = cub3d
build_dir = build
mlx_dir = minilibx_opengl_20191021
libft_dir = libft
include_dir = incs
lflags = -L$(libft_dir) -L$(mlx_dir)
iflags = -I. -I$(include_dir) -I$(libft_dir) -I/usr/include -I$(mlx_dir) -O3
cflags = -Wall -Wextra -Werror -g3

all : dirs $(name)

sanitize : cflags += -g3 -fsanitize=address -fsanitize=undefined
sanitize : lflags += -g3 -fsanitize=address -fsanitize=undefined
sanitize : all

$(libft_dir)/libft.a:
	make -C $(libft_dir)

$(mlx_dir)/libmlx.a:
	make -C $(mlx_dir)

PARSING_BUILD_DIR = $(build_dir)/parsing
COMMON_BUILD_DIR = $(build_dir)/common

PARSING_MODULES = validation texture_parsing valid_texture valid_map get_map check_characters
PARSING_OBJ = $(addprefix $(PARSING_BUILD_DIR)/, $(addsuffix .o, $(PARSING_MODULES)))
$(PARSING_BUILD_DIR) : | $(build_dir)
	mkdir $@


COMMON_MODULES = common
COMMON_OBJ = $(addprefix $(COMMON_BUILD_DIR)/, $(addsuffix .o, $(COMMON_MODULES)))
$(COMMON_BUILD_DIR): | $(build_dir)
	mkdir $@

depflags = -MT $@ -MMD -MP -MF $(build_dir)/$*.d

obj = $(build_dir)/cub3d.o $(PARSING_OBJ) $(COMMON_OBJ)

$(build_dir)/%.o: %.c $(build_dir)/%.d Makefile
	cc $(cflags) $(iflags) $(depflags) -c $< -o $@

$(name) : $(mlx_dir)/libmlx.a $(libft_dir)/libft.a $(obj)
	cc $(lflags) -o $@ $(obj) -lmlx -lft -framework OpenGL -framework AppKit

clean : $(mlx_dir)/Makefile
	rm -rf $(build_dir)
	make -C $(libft_dir) clean
	make -C $(mlx_dir) clean

fclean : clean
	make -C $(libft_dir) fclean
	rm -f $(name)

re : fclean all

.PHONY: all clean fclean re dirs

dirs: $(PARSING_BUILD_DIR) $(COMMON_BUILD_DIR)

$(build_dir):
	mkdir -p $@

$(obj:.o=.d):
include $(obj:.o=.d)
