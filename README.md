# About

Easy "clone and go" repository for a libopencm3 + FreeRTOS based project.

# Prerequisites

## 1. Install GNU Make

```bash
sudo apt install make
```

## 2. Install GCC ARM Toolchains

Download the toolchans from [https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads)

Choose *AArch32 bare-metal target (arm-none-eabi)* under your host system.

Extract the compressed file, move it to /opt and set the proper permissions.

```bash
tar xvf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 
cd /opt/gcc-arm/
sudo mv ~/Backup/linux/gcc-arm-none-eabi-10.3-2021.10/ .
sudo chown -R root:root gcc-arm-none-eabi-10.3-2021.10/
```
Check the version
```bash
/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc --version
```

# Instructions

Checkout, if you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)
```bash
git clone --recurse-submodules https://github.com/IOsetting/libopencm3-freertos-template.git your-project
```
In case anything goes wrong when cloning the submodules
```bash
cd your-project
git submodule update --init --recursive
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

# Examples

There are some example codes under *examples* folder, categoried by *none-os* and *rtos*. To try the code, just copy 
them to *user* and compile. Compile argument `FREERTOS=1` is required when compiling rtos examples, e.g.
```bash
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- FREERTOS=1 make -C user
```

# Directories

* user/  
  contains your application
* freertos/  
  contains FreeRTOS kernel source code
* libopencm3/  
  contains libopencm3 source code
* examples/  
  non-os and rtos demo codes

# License

This template should be considered released into the public domain. This only applies to the template code. 
libopencm3 and FreeRTOS themselves has their own licenses. You should replace this license with the license of your _own_ project if you are using this as a template.
