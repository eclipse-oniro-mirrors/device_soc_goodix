# device_gr551x

## 介绍

以下内容步骤参考[quickstart-lite-env-setup-linux](https://gitee.com/openharmony/docs/blob/master/zh-cn/device-dev/quick-start/quickstart-lite-env-setup-linux.md)

系统要求：Ubuntu16.04 和 Ubuntu18.04 64位系统版本。

编译环境搭建包含如下几步：


1. 安装必要的库和工具
2. 安装python3
3. 安装hb
4. 安装编译工具链
5. 获取源码
6. 确认目录结构
7. 编译流程
8. 烧录

## 工具安装

### 安装repo

1. 创建repo安装目录：命令行输入`mkdir ~/bin`
2. 下载repo：命令行输入`wget https://storage.googleapis.com/git-repo-downloads/repo -P ~/bin/`
3. 改变执行权限：命令行输入`chmod a+x ~/bin/repo`
4. 设置环境变量：在~/.bashrc文件的最后输入`export PATH=~/bin:$PATH`和`export REPO_URL=https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/`
5. 重启shell


### 安装必要的库和工具

> - 通常系统默认安装samba、vim等常用软件，需要做适当适配以支持Linux服务器与Windows工作台之间的文件共享。

> - 使用如下apt-get命令安装编译所需的必要的库和工具：

```
sudo apt-get install build-essential gcc g++ make zlib* libffi-dev e2fsprogs pkg-config flex bison perl bc openssl libssl-dev libelf-dev libc6-dev-amd64 binutils binutils-dev libdwarf-dev u-boot-tools mtd-utils gcc-arm-linux-gnueabi
```

### 安装Python3

1. 打开Linux编译服务器终端。
2. 输入如下命令，查看python版本号：

   ```
   python3 --version
   ```

   如果低于python3.7版本，不建议直接升级，请按照如下步骤重新安装。以python3.8为例，按照以下步骤安装python。

   1. 运行如下命令，查看Ubuntu版本：

   ```
   cat /etc/issue
   ```

   1. 根据Ubuntu不同版本，安装python。
      - 如果Ubuntu 版本为18+，运行如下命令。

        ```
        sudo apt-get install python3.8
        ```
      - 如果Ubuntu版本为16。

        a. 安装依赖包

        ```
        sudo apt update && sudo apt install software-properties-common
        ```

        b. 添加deadsnakes PPA 源，然后按回车键确认安装。

        ```
        sudo add-apt-repository ppa:deadsnakes/ppa
        ```

        c. 安装python3.8

        ```
        sudo apt upgrade && sudo apt install python3.8
        ```
3. 设置python和python3软链接为python3.8。

   ```
   sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 1
   sudo update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.8 1
   ```
4. 安装并升级Python包管理工具（pip3），任选如下一种方式。

   - **命令行方式：**

     ```
     sudo apt-get install python3-setuptools python3-pip -y
     sudo pip3 install --upgrade pip
     ```
   - **安装包方式：**

     ```
     curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
     python get-pip.py
     ```

### 安装hb

#### 前提条件

请先安装Python 3.7.4及以上版本，请见[安装Python3](#section1238412211211)。

#### 安装方法

1. 运行如下命令安装hb

   ```
   python3 -m pip install --user ohos-build
   ```
2. 设置环境变量

   ```
   vim ~/.bashrc
   ```

   将以下命令拷贝到.bashrc文件的最后一行，保存并退出。

   ```
   export PATH=~/.local/bin:$PATH
   ```

   执行如下命令更新环境变量。

   ```
   source ~/.bashrc
   ```
3. 执行"hb -h"，有打印以下信息即表示安装成功：

   ```
   usage: hb

   OHOS build system

   positional arguments:
     {build,set,env,clean}
       build               Build source code
       set                 OHOS build settings
       env                 Show OHOS build env
       clean               Clean output

   optional arguments:
     -h, --help            show this help message and exit
   ```

### 安装编译工具链

1. 编译链工具推荐使用gcc-arm-none-eabi-10-2020-q4-major。(下载网站：https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads )。
2. 执行`vim ~/.bashrc`。
3. 将工具链的路径加入环境变量, 如:`export PATH=/home/tools/ARM/gcc-arm-none-eabi-10-2020-q4-major/bin:$PATH`。
3. 保存后执行`source ~/.bashrc`使环境变量生效。

## 获取代码流程

1. 打包下载所有文件，此时默认的Harmony版本为Master：`repo init -u https://gitee.com/openharmony-sig/manifest.git -m devboard_gr5515.xml --no-repo-verify`。
2. 下载好仓库后，输入：`repo sync -c`，也就是下载当前分支的代码。
3. 下载好代码后，输入：`repo forall -c 'git lfs pull'`，下载部分大容量二进制文件。

## 确认目录结构

在device文件夹下，确保device/soc目录结构如下

```shell
user:~/Harmony/device/soc$ tree -L 3
.
└── goodix
    ├── BUILD.gn                                  # GN构建脚本
    ├── gr551x                                    # gr551x soc适配目录
    │   ├── adapter                               # 外设驱动、BLE、文件系统适配
    │   ├── BUILD.gn                              # GN构建脚本
    │   ├── components                            # 组件
    │   ├── drivers                               # HDF外设驱动
    │   ├── hcs                                   # 设备描述文件
    │   ├── Kconfig.liteos_m.defconfig.gr551x     # gr551x Kconfig默认配置
    │   ├── Kconfig.liteos_m.defconfig.series     # series Kconfig默认配置
    │   ├── Kconfig.liteos_m.series               # series Kconfig配置项
    │   ├── Kconfig.liteos_m.soc                  # soc Kconfig配置项
    │   ├── sdk_liteos                            # Liteos GR551x SDK适配
    │   └── tools                                 # 固件生成工具
    ├── Kconfig.liteos_m.defconfig                # liteos_m Kconfig默认配置
    ├── Kconfig.liteos_m.series                   # liteos_m series配置项
    └── Kconfig.liteos_m.soc                      # liteos_m soc配置项
```

在vendor文件夹下，确保vendor文件夹目录结构如下

```shell
user:~/Harmony/vendor$ tree -L 3

.
└── goodix
    ├── gr5515_sk_iotlink_demo   # BLE IOT应用示例工程
    │   ├── BUILD.gn             # GN构建脚本
    │   ├── config.json          # 子系统裁配置裁剪脚本
    │   ├── hals                 # 产品参数配置
    │   ├── hdf_config           # HDF硬件描述配置
    │   ├── kernel_configs       # Kconfig配置输出
    │   ├── patches              # 源码补丁
    │   └── patch.yml            # 补丁执行脚本
    └── gr5515_sk_xts_demo       # XTS测试示例工程
        ├── BUILD.gn             # GN构建脚本
        ├── config.json          # 子系统裁配置裁剪脚本
        ├── tests                # 测试用例
        ├── hals                 # 产品参数配置
        ├── hdf_config           # HDF硬件描述配置
        ├── kernel_configs       # Kconfig配置输出
        ├── patches              # 源码补丁
        └── patch.yml            # 补丁执行脚本
```

## 编译工程

进入源码根目录编译工程

   ​	`hb set -root .`   选择当前路径为工程根目录

   ​	`hb set -p `       选择工程

    goodix
        >gr5515_sk_xts_demo

   ​	`hb build -f --patch`  打patch并开始编译，后续修改了文件只需要执行`hb build -f`即可，不需要重复以上步骤。

如果hb set命令提示报错，请先执行一次`pip3 install build/lite`

## 固件烧录

生成的固件位于out/{board_name}/{product_name}/bin/application_fw.bin，固件烧录工具GProgrammer下载地址：https://product.goodix.com/zh/software_tool/gprogrammer 。

1. 将固件拷贝至Windows目录下；
2. 到Goodix官网下载最新的固件烧录工具GProgrammer.exe和对应的指导文档手册，安装后按照文档指导进行固件烧录。

## 相关仓库

[devboard_vendor_goodix_gr5515_sk_basic](https://gitee.com/openharmony-sig/devboard_vendor_goodix_gr5515_sk_basic)

[device_board_goodix](https://gitee.com/openharmony-sig/device_board_goodix)

