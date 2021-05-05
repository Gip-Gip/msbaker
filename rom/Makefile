PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

MCU := attiny84

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

 EXE := $(BIN_DIR)/msbaker.bin
 SRC := $(wildcard $(SRC_DIR)/*.c)
 OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
 
 CC=avr-gcc
 
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall -Os -mmcu=$(MCU)
LDFLAGS  := -Llib
LDLIBS   := -lm
 
.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
# Print the size of the binary
	avr-size -C $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

	 -include $(OBJ:.o=.d)