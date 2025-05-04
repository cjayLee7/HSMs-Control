/*****
  ** @file     : kernel_port.c/h
  ** @brief    : 端口定义
  ** @versions : newest
  ** @time     : newest
  ** @reviser  : unli (HeFei China)
  ** @explain  : null
*****/

#ifndef KERNEL_PORT_H
#define KERNEL_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

//C基本库
#include <stdint.h>		//基本数据类型
#include <stdbool.h>	//Bool数据类型
#include <string.h>		//变量类型,宏,字符数组函数
#include <stdlib.h>		//变量类型,宏,通用工具函数
#include <stdio.h>		//变量类型,宏,输入输出函数
//#include "arm_math.h"
//HAL库引用
#include "main.h"
#include "gpio.h"
//#include "spi.h"
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "dma.h"
////自建
//#include "loop.h"
//#include "./key/bsp_key.h" 
//#include "./sensors/Sensors.h"
////control
//#include "../control/control_config/control_config.h"// ./与../是有区别的，应该与文件夹层数有关

//固件版本
//#define XDrive_Firmware		"F1.1.5 S"

//硬件列表
//#define XDrive_REIN_Basic_H1_0		(0x00000100)	//(REIN - Basic - 01 - 00)
//#define XDrive_REIN_Basic_H1_1		(0x00000101)	//(REIN - Basic - 01 - 01)

//选中的硬件(在支持列表中选择型号)
//#define XDrive_Run		XDrive_REIN_Basic_H1_1

//引用板级宏
//#if   (XDrive_Run == XDrive_REIN_Basic_H1_0)
//	#include "XDrive_REIN_Basic_H1_0.h"
//#elif (XDrive_Run == XDrive_REIN_Basic_H1_1)
//	#include "XDrive_REIN_Basic_H1_1.h"
//#else
//	#error "Undefined XDrive_Run !!!"
//#endif

#ifdef __cplusplus
}
#endif

#endif
