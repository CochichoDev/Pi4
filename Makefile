RM := rm
CC := aarch64-none-elf-gcc
LD := aarch64-none-elf-ld
CP := cp
OBJCOPY := aarch64-none-elf-objcopy

FIRMWARE_DIR := firmware
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

DEPLOY_DIR := /home/cochicho/mnt

CPPFLAGS := -I$(INCLUDE_DIR)
CPFLAGS := -c -MMD -g -O0 -Wall -nostdlib
ASFLAGS := -c -Wall -MMD
LFLAGS := 

TARGET := kernel8.img

ELF := $(TARGET:.img=.elf)

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/*.S)
OBJ := $(foreach src,$(basename $(SRC)),$(addprefix $(BIN_DIR)/,$(notdir $(src))))
OBJ := $(foreach src,$(OBJ),$(addsuffix .o,$(src)))
DEP := $(OBJ:.o=.d)

LSCRIPT := lscript.ld

.PHONY: clean deploy all

all: $(TARGET)

$(TARGET): $(BIN_DIR)/$(ELF)
	@$(OBJCOPY) -O binary $< $(BIN_DIR)/$@
	@echo "$(TARGET) was generated"

$(BIN_DIR)/$(ELF): $(OBJ) $(LSCRIPT)
	@$(LD) $(LFLAGS) -T $(LSCRIPT) $(filter $(OBJ),$^) -o $@
	@echo "$@ was linked"

-include $(DEP)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CPPFLAGS) $(ASFLAGS) $< -o $@
	@echo "$< was compiled"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CPPFLAGS) $(CPFLAGS) $< -o $@
	@echo "$< was compiled"

deploy:
	$(RM) $(DEPLOY_DIR)/*
	$(CP) $(FIRMWARE_DIR)/* $(DEPLOY_DIR)/
	$(CP) $(BIN_DIR)/$(TARGET) $(DEPLOY_DIR)/
	sync
	@echo "Kernel deployed"

clean:
	@$(RM) -f $(BIN_DIR)/*
	@echo "TUI cleaned"
