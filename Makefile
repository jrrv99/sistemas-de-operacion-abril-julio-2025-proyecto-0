# Makefile para el proyecto Zelda Rogue

# Compilador y flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
LDFLAGS = -lm

# Directorios
SRC_DIR = src
BUILD_DIR = build
GAME_DIR = $(SRC_DIR)/game
UTILS_DIR = $(SRC_DIR)/utils

# Archivos fuente
SRCS = $(SRC_DIR)/main.c \
       $(GAME_DIR)/game.c \
       $(GAME_DIR)/player/Player.c \
       $(GAME_DIR)/world/dungeon/Dungeon.c \
       $(GAME_DIR)/world/items/Item.c \
       $(GAME_DIR)/world/items/Location.c \
       $(GAME_DIR)/world/village/Village.c \
       $(GAME_DIR)/world/world.c \
       $(UTILS_DIR)/utils.c

# Archivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/zelda_rogue.o

# Archivos de test
TEST_SRC = $(SRC_DIR)/test.c
TEST_OBJS = $(TEST_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
            $(UTILS_DIR)/utils.c:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_TARGET = $(BUILD_DIR)/test.o

# Regla por defecto
all: $(TARGET)

# Regla para crear el ejecutable principal
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para compilar archivos .c a .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar y ejecutar los tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Regla para crear el ejecutable de test
$(TEST_TARGET): $(BUILD_DIR)/test.o $(BUILD_DIR)/utils/utils.o
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Reglas especiales
.PHONY: all clean run test