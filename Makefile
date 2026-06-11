CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -Iinclude

BUILD_DIR = build
TARGET = main

.PHONY: app clean valgrind run

app: $(TARGET)

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/hash_table.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/hash_table.o -o $(TARGET)

$(BUILD_DIR)/main.o: src/main.c include/hash_table.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/hash_table.o: src/hash_table.c include/hash_table.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/hash_table.c -o $(BUILD_DIR)/hash_table.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET)