CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude

BUILD_DIR = build

.PHONY = app clean valgrind run

app: main

main: include/main.h src/main.c | $(BUILD_DIR)


clean:
	rm -rf build