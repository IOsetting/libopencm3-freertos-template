# About

Easy "clone and go" repository for a libopencm3 + FreeRTOS based project.

# Prerequisites

1. Install GNU Make
1. Install GCC ARM Toolchains

# Instructions

Checkout, if you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)
```bash
git clone --recurse-submodules https://github.com/IOsetting/libopencm3-freertos-template.git your-project
```
Build libopencm3, replace `PREFIX=..` with your toolchains path
```bash
cd your-project
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- make -C libopencm3
```
Build user project, replace `PREFIX=..` with your toolchains path
```bash
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- make -C user
```

# Directories

* user/ contains your application
* freertos/ contains FreeRTOS kernel source code
* libopencm3/ contains libopencm3 source code

# License

This template should be considered released into the public domain. This only applies to the template code. 
libopencm3 and FreeRTOS themselves has their own licenses. You should replace this license with the license of your _own_ project if you are using this as a template.