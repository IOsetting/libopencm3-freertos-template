ARM_TOOCHAIN 	?= /opt/gcc-arm/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
PREFIX 			?= $(ARM_TOOCHAIN)/arm-none-eabi-
OPENCM3_DIR		=../libopencm3
FREERTOS_DIR	=../freertos
PROJECT 		= app
DEVICE 			= stm32f103c8t6
BUILD_DIR 		= ../build

ifeq ($(FREERTOS), 1)
VPATH += $(FREERTOS_DIR)
VPATH += $(FREERTOS_DIR)/portable/GCC/ARM_CM3
VPATH += $(FREERTOS_DIR)/portable/MemMang
CFILES := $(wildcard *.c $(FREERTOS_DIR)/*.c $(FREERTOS_DIR)/portable/GCC/ARM_CM3/*.c)
CFILES += $(FREERTOS_DIR)/portable/MemMang/heap_4.c
# $(patsubst <pattern>, <replacement>, <text>)
INCLUDES += $(patsubst %,-I%, . $(FREERTOS_DIR)/include $(FREERTOS_DIR)/portable/GCC/ARM_CM3)
else
CFILES := $(wildcard *.c)
INCLUDES += $(patsubst %,-I%, .)
endif

CFILES := $(notdir $(CFILES))
AFILES := $(wildcard *.S)

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ./rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
