ARMGNU ?= aarch64-linux-gnu
QEMU_PWD ?= ../qemu-9.1.0-rc1/build/
board ?= rpi4

COPS += -DCONFIG_BOARD_PI4B
QEMU_FLAGS  += -machine raspi4b
# -fno-builtin 禁止编译器使用内建函数
# -nostdinc 此处是禁止编译标准库的头文件 
# -nostdlib 此处禁止链接标准库 
COPS += -g -Wall -nostdlib -nostdinc -Iinclude -fno-builtin
ASMOPS = -g -Iinclude 

BUILD_DIR = build
SRC_DIR = src
KERNEL_DIR = kernel
LIB_DIR = lib

all : panos.bin

clean :
	rm -rf $(BUILD_DIR) *.bin 

# 编译 src 目录下的 .c 文件 -MMD表示生产依赖文件
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(shell mkdir -p $(BUILD_DIR)/$(SRC_DIR))
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# 编译 kernel 目录下的 .c 文件
$(BUILD_DIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(shell mkdir -p $(BUILD_DIR)/$(KERNEL_DIR))
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# 编译 lib 目录下的 .c 文件
$(BUILD_DIR)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(shell mkdir -p $(BUILD_DIR)/$(LIB_DIR))
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# 编译 src 目录下的 .S 文件
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.S
	$(shell mkdir -p $(BUILD_DIR)/$(SRC_DIR))
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# 获取所有源文件
SRC_C_FILES = $(wildcard $(SRC_DIR)/*.c) 
KERNEL_C_FILES = $(wildcard $(KERNEL_DIR)/*.c)
LIB_C_FILES = $(wildcard $(LIB_DIR)/*.c)

ASM_FILES = $(wildcard $(SRC_DIR)/*.S)

# 将源文件转换为对象文件路径
OBJ_FILES = $(SRC_C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/$(SRC_DIR)/%.o)
OBJ_FILES += $(KERNEL_C_FILES:$(KERNEL_DIR)/%.c=$(BUILD_DIR)/$(KERNEL_DIR)/%.o)
OBJ_FILES += $(LIB_C_FILES:$(LIB_DIR)/%.c=$(BUILD_DIR)/$(LIB_DIR)/%.o)

OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/$(SRC_DIR)/%.o)

# 处理依赖文件
# DEP_FILES = $(OBJ_FILES:%.o=%.d)
# -include $(DEP_FILES)

# 链接生成最终的二进制文件
panos.bin: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/panos.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/panos.elf -O binary panos.bin

# QEMU运行配置
QEMU_FLAGS  += -nographic

run:
	$(QEMU_PWD)qemu-system-aarch64 $(QEMU_FLAGS) -kernel panos.bin
debug:
	$(QEMU_PWD)qemu-system-aarch64 $(QEMU_FLAGS) -kernel panos.bin -S -s
