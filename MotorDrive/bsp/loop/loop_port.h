/*****
  ** @file     : kernel_port.c/h
  ** @brief    : �˿ڶ���
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

//C������
#include <stdint.h>		//������������
#include <stdbool.h>	//Bool��������
#include <string.h>		//��������,��,�ַ����麯��
#include <stdlib.h>		//��������,��,ͨ�ù��ߺ���
#include <stdio.h>		//��������,��,�����������
//#include "arm_math.h"
//HAL������
#include "main.h"
#include "gpio.h"
//#include "spi.h"
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "dma.h"
////�Խ�
//#include "loop.h"
//#include "./key/bsp_key.h" 
//#include "./sensors/Sensors.h"
////control
//#include "../control/control_config/control_config.h"// ./��../��������ģ�Ӧ�����ļ��в����й�

//�̼��汾
//#define XDrive_Firmware		"F1.1.5 S"

//Ӳ���б�
//#define XDrive_REIN_Basic_H1_0		(0x00000100)	//(REIN - Basic - 01 - 00)
//#define XDrive_REIN_Basic_H1_1		(0x00000101)	//(REIN - Basic - 01 - 01)

//ѡ�е�Ӳ��(��֧���б���ѡ���ͺ�)
//#define XDrive_Run		XDrive_REIN_Basic_H1_1

//���ð弶��
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
