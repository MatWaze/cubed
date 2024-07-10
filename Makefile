name = cub3d
build_dir = build
mlx_dir = mlx_linux 
libft_dir = libft
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

PARSING_BUILD_DIR=$(build_dir)/parsing

PARSING_MODULES = parsing
PARSING_OBJ = $(addprefix $(PARSING_BUILD_DIR/), $(addsuffix .o, $(PARSING_MODULES)))
$(PARSING_BUILD_DIR) : | $(build_dir)
	mkdir $@

depflags = -MT $@ -MMD -MP -MF $(build_dir)/$*.d

obj = $(build_dir)/cub3d.o $(PARSING_OBJ)

$(build_dir)/%.o: %.c $(build_dir)/%.d Makefile
	cc $(cflags) $(iflags) $(depflags) -c $< -o $@

$(name) : $(mlx_dir)/libmlx.a $(libft_dir)/libft.a $(obj)
	cc $(lflags) -o $@ $(obj) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

clean : $(mlx_dir)/Makefile
	rm -rf $(build_dir)
	make -C $(libft_dir) clean
	make -C $(mlx_dir) clean

fclean : clean
	make -C $(libft_dir) fclean
	rm -f $(name)

re : fclean all

.PHONY: all clean fclean re dirs

dirs: $(PARSING_BUILD_DIR)

$(build_dir):
	mkdir $@

$(obj:.o=.d):
include $(obj:.o=.d)