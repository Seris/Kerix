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
CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib

# Import options
include kerix.config

# Setting archdir
ARCHDIR := arch/$(ARCH)

# Directories for compilation
INCLUDEDIR := include
SUBDIRS    := libk init kernel $(ARCHDIR)

# Import arch options
include $(ARCHDIR)/make.config

# Sources
SRC_FILES := $(shell find $(SUBDIRS) -name "*.c" -or -name "*.S")

# Future object files
OBJ_LIST = $(shell FILES="$(SRC_FILES)"; \
	for file in $$FILES; do echo $${file%.*}.o; done;)

.PHONY: all clean

# Build Kerix
all: $(OBJ_LIST) $(ARCHDIR)/setup.ld
	@ echo "Linking the kernel"
	ld $(LDFLAGS) -T $(ARCHDIR)/setup.ld -o $(OUTPUT) $(OBJ_LIST)
	@ echo "Kerix builded at $(OUTPUT)"

%.o: %.c
	@ echo "Compile $< => $@"
	@ $(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDEDIR) $(LIBS)

%.o: %.S
	@ echo "Compile $< => $@"
	@ $(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDEDIR) $(LIBS)

# Clean object file
clean:
	@ echo "Cleaning $(CURDIR)/$(DIR)"
	@ - rm -f $(shell find $(CURDIR)/$(DIR) -name "*.o" -or -name "*.a")


# Rebuild kerix
rebuild:
	@ $(MAKE) clean all


# Rules to work with QEMU
qemu-start:
	qemu-system-$(ARCH) -kernel $(OUTPUT) $(QEMU_FLAGS)

qemu-start-with-gdb-server:
	qemu-system-$(ARCH) -kernel $(OUTPUT) $(QEMU_FLAGS) -s -S

gdb-connect-qemu:
	objcopy --only-keep-debug $(OUTPUT) /tmp/kerix.debug
	- gdb -s /tmp/kerix.debug -ex "target remote localhost:1234" ; \
	rm -f /tmp/kerix.debug ; \
	killall qemu-system-$(ARCH)

kill-qemu:
	killall qemu-system-$(ARCH)