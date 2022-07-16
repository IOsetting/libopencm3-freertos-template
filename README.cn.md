# 关于

基于 libopencm3 + FreeRTOS 的项目模板

# 前提

## 1. 安装 GNU Make

```bash
sudo apt install make
```

## 2. 安装 GCC ARM Toolchains

从ARM网站下载工具链 [https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads)

根据操作系统选择 *AArch32 bare-metal target (arm-none-eabi)* 版本

解压, 移动, 设置权限
```bash
tar xvf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 
cd /opt/gcc-arm/
sudo mv ~/Backup/linux/gcc-arm-none-eabi-10.3-2021.10/ .
sudo chown -R root:root gcc-arm-none-eabi-10.3-2021.10/
```
检查版本
```bash
/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc --version
```

# 使用说明

将仓库克隆到本地, 如果使用的是旧版本 git, 或者clone时忘了使用初始化子模块参数 ```--recurse-submodules```, 
可以运行 ```git submodule update --init``` 进行初始化(仅需要运行一次)
```bash
git clone --recurse-submodules https://github.com/IOsetting/libopencm3-freertos-template.git your-project
```
如果克隆过程中出问题, 进入到目录下用下面的命令可以重新导出子模块
```bash
cd your-project
git submodule update --init --recursive
```
编译 libopencm3, 将命令中的 `PREFIX=..` 替换成你的工具链路径
```bash
cd your-project
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- make -C libopencm3
```
构建用户项目, 同样将命令中的 `PREFIX=..` 替换成你的工具链路径
```bash
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- make -C user
```

# 示例代码

在*examples*目录下有一些示例代码, 分为*非rtos*和*rtos*两类, 如果要运行示例代码, 只需要选择示例并将对应的代码复制到*user*目录下
然后编译. 对于rtos示例, 需要带上编译参数`FREERTOS=1`, 例如
```bash
PREFIX=/opt/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi- FREERTOS=1 make -C user
```


# 目录

* user/  
  用户应用目录
* freertos/  
  FreeRTOS  kernel 代码
* libopencm3/  
  libopencm3 代码
* examples/  
  non-os 和 rtos 示例代码

# 授权

本模板使用的 Apache-2.0 协议, 仅仅应用于模板的代码本身. libopencm3 和 FreeRTOS 有各自的协议. 
如果使用这个模板创建项目, 应该将协议换成自己的协议.
