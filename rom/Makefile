PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

MCU := attiny84a

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

 EXE := $(BIN_DIR)/msbaker.bin
 HEX := $(BIN_DIR)/msbaker.hex
 SRC := $(wildcard $(SRC_DIR)/*.c)
 OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
 
 CC=avr-gcc
 
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall -Os -mmcu=$(MCU) -DF_CPU=10000000
LDFLAGS  := -Llib -mmcu=$(MCU) -DF_CPU=10000000
LDLIBS   := -lm
 
.PHONY: all clean

all: $(HEX)

$(HEX): $(EXE)
	avr-objcopy -O ihex $(EXE) $@

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
# Print the size of the binary
	avr-size -C $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

flash: $(HEX)
	avrdude -p t84 -c avrispv2 -U flash:w:$(HEX) -F -P /dev/ttyACM0

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

	 -include $(OBJ:.o=.d)