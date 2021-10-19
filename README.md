# 快速上手GR5515 SK鸿蒙开发板

## 代码下载

### 安装repo

1. 创建repo安装目录：命令行输入mkdir ~/bin
2. 下载repo：命令行输入wget https://storage.googleapis.com/git-repo-downloads/repo -P ~/bin/
3. 改变执行权限：命令行输入chmod a+x ~/bin/repo
4. 设置环境变量：在~/.bashrc文件的最后输入export PATH=~/bin:$PATH和export REPO_URL=https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/
5. 重启shell

### 下载系统

笔者使用的版本是1.1.2_LTS（基于1.0.1_release分支），仅在此版本进行了验证，建议读者下载此版本的鸿蒙系统源码。

步骤1，步骤2选择其中一步进行。

1. 下载1.1.2_LTS指定标签的命令为：repo init -u https://gitee.com/openharmony/manifest.git -b refs/tags/OpenHarmony-v1.1.2-LTS --no-repo-verify。
2. 打包下载所有文件，此时默认鸿蒙版本为1.0.1_release：repo init -u https://gitee.com/openharmony-sig/manifest.git -b OpenHarmony_1.0.1_release --no-repo-verify -m devboard_gr5515.xml。
3. 下载好仓库后，输入：repo sync -c，也就是下载当前分支的代码。
4. 下载好代码后，输入：repo forall -c 'git lfs pull'，下载部分大容量二进制文件。



### 下载GR5515源码

如果下载系统时选择了打包下载，可跳过此步。

1. 从https://gitee.com/openharmony-sig/devboard_device_goodix_gr551x.git          下载device仓内容。
2. 从https://gitee.com/openharmony-sig/devboard_vendor_goodix_gr5515_sk_basic.git 下载vendor仓内容。



## 确认目录结构

在device文件夹下，确保device文件夹目录结构如下

```shell
user:~/Harmony/device$ tree -L 3
.
└── goodix
    └── gr551x
        ├── adapter
        ├── bin_create.py
        ├── BUILD.gn
        ├── Core
        ├── gr551x.ld
        ├── GR551x_SDK
        ├── liteos_m
        ├── los_base.h
        ├── ohosdemo
        ├── sdk_main.c
        └── target_config.h

```
在vendor文件夹下，确保vendor文件夹目录结构如下

```shell
user:~/Harmony/vendor$ tree -L 3
.
└── goodix
    └── gr5515_sk
        ├── bin_create.py
        ├── BUILD.gn
        ├── config.json
        ├── hals
        └── user
```

## 设置编译工具链

1. 编译链工具推荐gcc-arm-none-eabi-10-2020-q4-major。（下载网站：https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads）
2. 执行vim ~/.bashrc
3. 将工具链的路径加入环境变量, 如:export PATH=/home/tools/ARM/gcc-arm-none-eabi-10-2020-q4-major/bin:$PATH
3. 保存后执行source ~/.bashrc使环境变量生效

## 编译鸿蒙工程

进入鸿蒙源码根目录编译工程

   ​	hb set       选择gr5515_sk

   ​	hb build -f  编译通过，后续修改了文件只需要执行hb build -f即可，不需要重复以上步骤。

## 镜像烧录

生成的镜像位于out/gr551x/gr551x_sk/bin，固件转换工具位于device/goodix/gr551x/GR551x_SDK/tools
固件烧录工具GProgrammer下载地址：https://product.goodix.com/zh/software_tool/gprogrammer

1. 将device/goodix/gr551x/GR551x_SDK目录下tools文件夹拷贝到Windows下，然后将out/gr551x/gr551x_sk/bin目录下的application.bin拷贝到tools文件夹
2. 在tools目录下，点击after_build.bat脚本，对原始的application.bin进行转换处理，转换后固件输出到当前目录的ble_tool_bin文件夹下，application_fw.bin即是待烧录的最终固件
3. 到Goodix官网下载最新的固件烧录工具GProgrammer和对应的指导文档手册，安装后按照文档进行固件烧录

## 常见错误排查


