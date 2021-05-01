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
uint64_t UtzBytesToIA(uint8_t* data);

// IAToBytes ��IA��ַת��Ϊ�ֽ���.�ֽ����Ǵ��
void UtzIAToBytes(uint64_t ia, uint8_t* data);

// UtzMemcpyReverse ��ת����.����srcΪС�˴洢.����ת��Ϊ��˴洢��dst��
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

// GetNextHeadLen �õ���һͷ���ֽ���
// ע��:��һͷ������������ͷ��
// bytes��֡�������ֽ���,size��֡�����ֽ���.offset����һͷ����ƫ����
// ����ֵ����һͷ���ֽ���.�����0��ʾ����ʧ��
int UtzGetNextHeadLen(uint8_t* bytes, int size, int offset);

// UtzIAStrToHex IA��ַ�ַ���ת����
bool UtzIAStrToHex(const char* src, uint64_t* dst);

// UtzIAToStr IA��ַת�ַ�����ʽ
// type��0����׼�����1��ǰ��0ѹ����2��ȫ0ѹ�����
bool UtzIAHexToStr(uint64_t src, char* dst, int type);

#endif
