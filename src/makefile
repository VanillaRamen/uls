.default: uls

uls: main.c
	gcc -o uls \
		main.c \
		-Wall -Wextra -Wconversion \
		-lc

uls_debug: main.c
	gcc -o uls_debug \
		main.c \
		-Wall -Wextra -Wconversion \
		-lc \
		-O0 -Werror
