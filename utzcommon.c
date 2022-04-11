// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// ͨ��ģ��
// Authors: jdh99 <jdh821@163.com>

#include "utzcommon.h"
#include "utznlp.h"
#include "tzbox.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// �ڴ����id
static int mid = -1;

// UtzGetMid ��ȡ�ڴ�id
int UtzGetMid(void) {
    if (mid == -1) {
        mid = TZMallocRegister(0, UTZ_TAG, UTZ_MALLOC_SIZE);
        if (mid == -1) {
            LE(UTZ_TAG, "malloc register failed!");
        }
    }
    return mid;
}

// BytesToIA ���ֽ�����ȡ��IA��ַ.�ֽ����Ǵ��
// �ֽ������ȱ��뱣֤����IA_LEN
uint32_t UtzBytesToIA(uint8_t* data) {
    uint32_t ia = 0;
    UtzMemcpyReverse((uint8_t*)&ia, data, UTZ_IA_LEN);
    return ia;
}

// IAToBytes ��IA��ַת��Ϊ�ֽ���.�ֽ����Ǵ��
void UtzIAToBytes(uint32_t ia, uint8_t* data) {
    UtzMemcpyReverse(data, (uint8_t*)&ia, UTZ_IA_LEN);
}

// UtzMemcpyReverse ��ת����.����srcΪС�˴洢.����ת��Ϊ��˴洢��dst��
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}
