# Kerix Makefile
VERSION    := 0
SUBVERSION := 0
PATCHLEVEL := 1
NAME       := Rainbow Vampire Kitten
export VERSION SUBVERSION PATCHLEVEL NAME

# Avoid funny character set dependencies && interference with shell env settings
unexport LC_ALL GREP_OPTIONS
LC_COLLATE := C
LC_NUMERIC := C
export LC_COLLATE LC_NUMERIC

MAKEFLAGS += --no-print-directory

# Flags
CFLAGS:=$(CFLAGS)-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -lgcc 


# Import options
include kerix.config

# Directories for compilation
INCLUDEDIR := include
SUBDIRS    := libk boot kernel

# Sources
SRC_FILES := $(shell find $(SUBDIRS) -name "*.c" -or -name "*.S")

# Future object files list
OBJ_LIST = $(shell FILES="$(SRC_FILES)"; \
	for file in $$FILES; do echo $${file%.*}.o; done;)

.PHONY: all clean

# Build Kerix
all:
	@ printf "\e[0;35mNow building Kerix - ${NAME} (${VERSION}.${SUBVERSION}.${PATCHLEVEL})\e[m\n\n"
	@ $(MAKE) $(OUTPUT) || { printf "\n\e[0;31mBuild failed\e[m\n"; exit 1; }
	@ printf "\n\e[0;32mKerix builded at $(OUTPUT)\e[m\n"

$(OUTPUT): $(OBJ_LIST) setup.ld
	@ printf "\n\e[0;33mLinking the kernel\n\e[0;36m"
	$(CC) $(CFLAGS) $(LDFLAGS) -T setup.ld -o $(OUTPUT) $(OBJ_LIST)

%.o: %.c
	@ printf "\e[0;33mCompile $< => $@\e[0;36m\n"
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDEDIR)
	@ printf "\e[m"

%.o: %.S
	@ printf "\e[0;33mCompile $< => $@\e[0;36m\n"
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDEDIR)
	@ printf "\e[m"

# Clean object file
clean:
	@ printf "\e[0;33mCleaning $(CURDIR)/$(DIR)\e[0;36m\n"
	- rm -f $(shell find $(CURDIR)/$(DIR) -name "*.o" -or -name "*.a")
	@ printf "\e[m\n"


# Rebuild kerix
rebuild:
	@ $(MAKE) clean all


# Rules to work with QEMU
qemu-start:
	$(QEMU) -kernel $(OUTPUT) $(QEMU_FLAGS) -pidfile $(QEMU_PID_FILE)

connect-gdb:
	- $(GDB) -s $(DEBUG_FILE) -ex "target remote $(QEMU_ADDRESS):$(QEMU_PORT)" ; \
	rm -f /tmp/kerix.debug ; \
	make kill-qemu

gen-debug-file:
	objcopy --only-keep-debug $(OUTPUT) $(DEBUG_FILE)
	objcopy --strip-debug $(OUTPUT)

kill-qemu:
	- kill $(shell cat $(QEMU_PID_FILE))
	- rm -f $(QEMU_PID_FILE)
