# devboard_device_goodix_gr551x

#### 介绍
{**以下是 Gitee 平台说明，您可以替换此简介**
Gitee 是 OSCHINA 推出的基于 Git 的代码托管平台（同时支持 SVN）。专为开发者提供稳定、高效、安全的云端软件开发协作平台
无论是个人、团队、或是企业，都能够用 Gitee 实现代码托管、项目管理、协作开发。企业项目请看 [https://gitee.com/enterprises](https://gitee.com/enterprises)}

#### 软件架构
软件架构说明


#### 安装教程

# OpenHarmony GR5515 SK快速上手


## 搭建编译环境

安装Ubuntu 18.04环境

```bash
# 安装必要的包
sudo apt update
sudo apt install -y binutils git git-lfs gnupg flex bison gperf build-essential \
                    zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 \
                    lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z-dev ccache \
                    libgl1-mesa-dev libxml2-utils xsltproc unzip m4 wget bc python python3 \
                    android-tools-fsutils libssl-dev mtools

# 安装repo
curl https://gitee.com/oschina/repo/raw/fork_flow/repo-py3 | sudo tee /usr/local/bin/repo >/dev/null
sudo chmod a+x /usr/local/bin/repo

# 安装hb
python3 -m pip uninstall ohos-build
python3 -m pip install --user ohos-build

# 将/bin/sh设置为/bin/bash
sudo ln -sf bash /bin/sh

# 设置git信息
git config --global user.name your_name
git config --global user.email your_email
```


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request



