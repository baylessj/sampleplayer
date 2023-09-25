# Project Name
TARGET = sampleplayer

# Sources
CPP_SOURCES = src/main.cpp src/sample.cpp
# Library Locations
LIBDAISY_DIR = ./libdaisy
DAISYSP_DIR = ./DaisySP

APP_TYPE=BOOT_QSPI

default:
	$(MAKE) all
	$(MAKE) program-dfu

libraries:
	cd DaisySP && make && cd ../libdaisy && make && cd ..

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Include terrarium.h
C_INCLUDES += -I./Terrarium -I./DaisySP/Source
