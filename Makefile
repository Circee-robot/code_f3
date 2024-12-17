DEBUG:=putain

default: all

Makefile_path := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

#must give the full path to have clang work properly !
Toolchain = /usr/bin/arm-none-eabi-

CC = $(Toolchain)gcc
CFlags =
CXX= $(Toolchain)g++
CXXFlags =
LD = $(Toolchain)ld
LFlags =
GDB := $(Toolchain)gdb

# Patch for ubuntu
ifeq (, $(shell which $(GDB)))
ifeq (, $(shell which gdb-multiarch))
else
	GDB := gdb-multiarch
endif
endif

ifeq (, $(shell which ccache))
else
	CC := ccache $(CC)
	CXX:= ccache $(CXX)
endif

# Generic flags
CFlags += \
	-std=gnu11 \
	-fdiagnostics-color=always \
	-Wall \
	-Wextra


ifdef DEBUG
	CFlags += -O0
else
	CFlags += -Os
endif

CXXFlags += \
	-std=gnu++14

LFlags += \
	-Wl,--gc-sections \
	-nostartfiles \
	-lm \
	-lstdc++_nano \
	-lc \
	-lg \
	-lrdimon \
	-lnosys #stub functions for posix function library


# MCU specific flags (stm32f401re)
LINKER_SCRIPTS_DIR = $(Makefile_path)/hal_common/linker_scripts

CFlags += \
	-mcpu=cortex-m4 \
	-mthumb \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-specs=nano.specs

	# Use LibOpenCm3
LIBOPENCM3_DIR = $(Makefile_path)/hal_common/libopencm3
CFlags += -I $(LIBOPENCM3_DIR)/include -DSTM32F3
LFlags += -L $(LIBOPENCM3_DIR)/lib -lopencm3_stm32f3

# Openocd configuration
OPENOCD_CFG = /usr/share/openocd/scripts/board/st_nucleo_f3.cfg
# OPENOCD_BIN = /home/beatrice/circee/xpack-openocd-0.11.0-5/bin/openocd
OPENOCD_BIN = /home/beatrice/circee/xpack-openocd-0.11.0-1//bin/openocd
# OPENOCD_BIN = openocd
OPENOCD_ARCH := ../openocd/xpack-openocd-0.11.0-1/bin/openocd

LFlags += -T $(LINKER_SCRIPTS_DIR)/stm32f303.ld


#include our directories with .h files
#add directories separated by whitespaces in INCPATHS
#a reparer
INCPATHS=lowlevel/include test/include #$(DIR2) ...

INC_PARAMS=$(foreach d, $(INCPATHS), -I $d)

CFlags += $(INC_PARAMS)

libopencm3:
	$(MAKE) -C $(LIBOPENCM3_DIR) -j

all: mainTest.flash

%.cpp.o: %.cpp Makefile
	@$(CXX) $(CFlags) $(CXXFlags) $< -o $@ -c
	@echo CXX $<

%.o: %.c Makefile
	$(CC) $(CFlags) $< -o $@ -c
	@echo CC $<


pathMainTest = lowlevel test

srcMainTest = $(foreach d, $(pathMainTest), $(wildcard $d/*.c))

objMainTest = $(foreach d, $(srcMainTest) , $(d:.c=.o) )

depsMainTest := $(objMainTest:.o=.d)

#/usr/bin/arm-none-eabi-strip mainTest.elf --strip-debug
mainTest.elf: $(objMainTest) \
	mainTest.c
	#debug
	#@echo $(objMainTest)
	#
	$(CC) $(CFlags) $^ $(LFlags) -o $@
	@echo LINK $@

%.d: %.c
	@$(CC) $(CFlags) $< -MM -MT $(@:.d=.o) >$@



#compiled version to be uploaded on the chip
%.hex: %.elf
	@arm-none-eabi-objcopy -Oihex $^ $@
	@echo OBJCOPY $@


#please do not put sudo before openocd, please run
#sudo usermod -a -G uucp <user> for serial monitor
#for udev rule:
#nano /etc/udev/rules.d/70-st-link.rules
#  #NUCLEO ST-LINK/V2.1
#  ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b",TAG+="uaccess"
#to find theses values lsusb
#then udevadm control --reload-rules
#unplug and plug st-link

#script to add permissions to flash
install_udev:
	@echo "Installing udev rules…"
	@sudo ./install_udev.sh
	@echo "Now, unplug and re-plug the st-link."

#to flash onto the chip
%.flash: %.hex
	$(OPENOCD_BIN) -f $(OPENOCD_CFG) \
		-c "init" \
		-c "reset init" \
		-c "flash write_image erase $^" \
		-c "reset" \
		-c "shutdown"

OPENOCD_TELNET_PORT := 2222
OPENOCD_GDB_PORT := 2223
# Debugging with GDB
%.gdb: %.elf
	$(OPENOCD_BIN) -c "telnet_port $(OPENOCD_TELNET_PORT);gdb_port $(OPENOCD_GDB_PORT)" -f $(OPENOCD_CFG) >openocd.log 2>&1 &
	$(GDB) $^ -ex 'target extended-remote :$(OPENOCD_GDB_PORT)'
	{ echo "shutdown"; sleep 0.1; } | telnet 127.0.0.1 $(OPENOCD_TELNET_PORT)

clean:
		find . \
		\( -not -path  "./hal_common*" \) \
		\( -name "*.o" \
		-o -name "*.a" \
		-o -name "*.hex" \
		-o -name "*.elf" \
		-o -name "*.d" \
		-o -name "*.log" \
		\) -delete
