// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// ͨ��ģ��
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_COMMON_H
#define UTZ_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#define UTZ_TAG "utz"
#define UTZ_MALLOC_SIZE 4096

// UtzGetMid ��ȡ�ڴ�id
int UtzGetMid(void);

// BytesToIA ���ֽ�����ȡ��IA��ַ.�ֽ����Ǵ��
// �ֽ������ȱ��뱣֤����IA_LEN
uint32_t UtzBytesToIA(uint8_t* data);

// IAToBytes ��IA��ַת��Ϊ�ֽ���.�ֽ����Ǵ��
void UtzIAToBytes(uint32_t ia, uint8_t* data);

// UtzMemcpyReverse ��ת����.����srcΪС�˴洢.����ת��Ϊ��˴洢��dst��
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

#endif
