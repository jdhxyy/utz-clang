// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// ͨ��ģ��
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_COMMON_H
#define UTZ_COMMON_H

#include <stdint.h>
#include <stdbool.h>

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

// UtzHtons 2�ֽ�������ת��Ϊ������
uint16_t UtzHtons(uint16_t n);

// UtzNtohs 2�ֽ�������ת��Ϊ������
uint16_t UtzNtohs(uint16_t n);

// UtzHtonl 4�ֽ�������ת��Ϊ������
uint32_t UtzHtonl(uint32_t n);

// UtzNtohl 4�ֽ�������ת��Ϊ������
uint32_t UtzNtohl(uint32_t n);

// UtzHtonll 8�ֽ�������ת��Ϊ������
uint64_t UtzHtonll(uint64_t n);

// UtzNtohll 8�ֽ�������ת��Ϊ������
uint64_t UtzNtohll(uint64_t n);

#endif
