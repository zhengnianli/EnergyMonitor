# 基于合泰单片机的高校公寓远程能源监控系统   




## 1、前言

合泰半导体隶属台湾盛群半导体集团，合泰杯单片机应用设计竞赛的比赛形式为：作品自由发挥，要在几个月之内完成，且必须使用合泰单片机。比赛分为三个环节：初赛、复赛、决赛，每一环节都会刷掉一部分队伍。


## 2、作品分享
### 2.1 作品简介

这是我们团队2017年合泰杯省一等奖作品。本作品以合泰`HT32F1656`为终端主控，采集公寓当前用电用水数据，并将采集到的数据通过终端无线`WIFI`发送至云端服务器，通过电脑Web端或手机APP远程查看数据，并可通过电脑Web端或手机APP随时随地远程控制公寓开关水电。通过测试结果证明本作品很好的解决了上述公寓用水用电的诸多诟病，实现了智能的公寓生活。并且，设备终端也配备有显示屏，可实时显示一些用水用电等数据。

### 2.2 作品模块构成图及系统框图

### 2.2.1 系统框图

本系统主要由`电源模块`、`存储模块`、`继电器控制模块`、`无线WiFi模块`、`显示控制模块`、`环境温度采集模块`、`电能信息采集模块`和`用水采集模块`组成，系统控制芯片为`HT32F1656`。该系统方框图如下图所示：

[![ZkmOu6.md.png](https://s2.ax1x.com/2019/06/24/ZkmOu6.md.png)](https://imgchr.com/i/ZkmOu6)


### 2.2.2 模块构成图

[![ZkmxED.md.png](https://s2.ax1x.com/2019/06/24/ZkmxED.md.png)](https://imgchr.com/i/ZkmxED)


## 3、人机交互过程图及云端监测

### 3.1 人机交互过程图

电脑Web端、手机APP端是基于中移动ONENET云平台搭建的，基于ONENET提供的接入协议和平台功能，用户终端与电脑Web端、手机APP、云服务器共同构建了一套完整的能源测控系统。用户终端即时的将数据推送至云平台，云平台根据推送的数据进行云端和手机APP端同步更新。电脑Web端、手机APP端通过发送指令控制终端。如图所示：

[![Zkn1K0.md.png](https://s2.ax1x.com/2019/06/24/Zkn1K0.md.png)](https://imgchr.com/i/Zkn1K0)



### 3.2 云端监测过程图

[![Zkn8bT.md.png](https://s2.ax1x.com/2019/06/24/Zkn8bT.md.png)](https://imgchr.com/i/Zkn8bT)

## 4、程序流程图

### 4.1 主流程图

[![ZknDr6.md.png](https://s2.ax1x.com/2019/06/24/ZknDr6.md.png)](https://imgchr.com/i/ZknDr6)

### 4.2 与云端通信流程图

[![ZknfxI.md.png](https://s2.ax1x.com/2019/06/24/ZknfxI.md.png)](https://imgchr.com/i/ZknfxI)


## 5、作品图片

### 5.1 设备终端实物图

[![ZkuFJJ.md.png](https://s2.ax1x.com/2019/06/24/ZkuFJJ.md.png)](https://imgchr.com/i/ZkuFJJ)

[![ZkuVQ1.md.png](https://s2.ax1x.com/2019/06/24/ZkuVQ1.md.png)](https://imgchr.com/i/ZkuVQ1)



### 5.2 Onenet云端监测图

在WEB端显示采集的用水用电情况，及断水断电开关进行控制如下图所示：

[![ZkuKoD.md.png](https://s2.ax1x.com/2019/06/24/ZkuKoD.md.png)](https://imgchr.com/i/ZkuKoD)

### 5.3 设备终端UI界面

我们的设备终端屏幕使用的是串口屏，关于串口屏在往期笔记中已经有分享：[基于STM32的智能天气预报系统](https://zhengnianli.github.io/2018/11/21/zuo-pin-ji-yu-stm32-de-zhi-neng-tian-qi-yu-bao-xi-tong/)

### 5.3.1 UI界面方案一：

[![ZkKxET.md.png](https://s2.ax1x.com/2019/06/24/ZkKxET.md.png)](https://imgchr.com/i/ZkKxET)
[![ZkMJVf.md.png](https://s2.ax1x.com/2019/06/24/ZkMJVf.md.png)](https://imgchr.com/i/ZkMJVf)
[![ZkMaGQ.md.png](https://s2.ax1x.com/2019/06/24/ZkMaGQ.md.png)](https://imgchr.com/i/ZkMaGQ)
[![ZkM6aT.md.png](https://s2.ax1x.com/2019/06/24/ZkM6aT.md.png)](https://imgchr.com/i/ZkM6aT)
[![ZkQne0.md.png](https://s2.ax1x.com/2019/06/24/ZkQne0.md.png)](https://imgchr.com/i/ZkQne0)
[![ZkQ8SJ.md.png](https://s2.ax1x.com/2019/06/24/ZkQ8SJ.md.png)](https://imgchr.com/i/ZkQ8SJ)
[![ZkQy6A.md.png](https://s2.ax1x.com/2019/06/24/ZkQy6A.md.png)](https://imgchr.com/i/ZkQy6A)

### 5.3.2 UI界面方案二：

[![Zklm1H.md.png](https://s2.ax1x.com/2019/06/24/Zklm1H.md.png)](https://imgchr.com/i/Zklm1H)
[![ZklMnI.md.png](https://s2.ax1x.com/2019/06/24/ZklMnI.md.png)](https://imgchr.com/i/ZklMnI)


### 5.3.3 自拍图

最后放个自恋的自拍图，哈哈~

[![ZklXDI.md.png](https://s2.ax1x.com/2019/06/24/ZklXDI.md.png)](https://imgchr.com/i/ZklXDI)

## 6、代码获取
>https://github.com/zhengnianli/EnergyMonitor

该代码工程是在keil下创建的，但是要安装合泰单片机相关插件（可能会存在兼容性问题），可在我的微信公众号后台回复关键词：能源监控，即可获取该作品代码及keil插件。若安装插件打不开，可使用source insight代码阅读器进行阅读，关于source insight的介绍可查看往期分享：[这么好用的代码阅读器你装了吗？](https://zhengnianli.github.io/2018/11/12/gong-ju-zhe-me-hao-yong-de-dai-ma-yue-du-qi-ni-zhuang-liao-ma/)


---

我的个人博客为：https://zhengnianli.github.io

我的微信公众号为：嵌入式大杂烩

[![VcSFJJ.md.png](https://s2.ax1x.com/2019/06/11/VcSFJJ.md.png)](https://imgchr.com/i/VcSFJJ)
