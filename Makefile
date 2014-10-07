VERSION    := 0
SUBVERSION := 0
PATCHLEVEL := 1
NAME       := Rainbow Vampire Kitten
export VERSION SUBVERSION PATCHLEVEL NAME

MAKEFLAGS += -rR --no-print-directory

# Program name
SHELL   := /bin/bash
DIRNAME := dirname
PRINTF  := printf
MKDIR   := mkdir
MAKE    := make
ECHO    := echo
EXIT    := exit
FIND    := find
GREP    := grep
SED			:= sed
CAT 		:= cat
LD      := ld
LN 			:= ln
LS      := ls
RM      := rm
export MAKEFLAGS SHELL PRINTF MKDIR MAKE ECHO EXIT FIND GREP SED CAT LD LN LS RM

unexport LC_ALL GREP_OPTIONS
LC_COLLATE := C
LC_NUMERIC := C
export LC_COLLATE LC_NUMERIC


# Kerix tree
root   		  := $(CURDIR)
srctree  		:= src
tmpdir   		:= /tmp/kerix-build
virtualtree := ${tmpdir}/virtualtree
includes    := ${tmpdir}/virtualtree/includes
export root srctree virtualtree includes

# Import options
include ./kerix.opt.mk

# Setting archtree
archtree := arch/$(ARCH)
export archtree

# Build and link Kerix
all:
	@ ${SHELL} build.sh

# Clean target
clean_tree:
	$(RM) -rf ${virtualtree}