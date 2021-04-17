// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3��Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_FLP_H
#define UTZ_FLP_H

#include <stdint.h>
#include <stdbool.h>

// �汾
#define UTZ_FLP_VERSION_NAME "1.2"

// ���β׺����
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToFlpFrame �ֽ���ת��ΪFLP֡
// fixedLenΪ0��ʾ���ǹ̶�����֡,����Ҫβ׺
// ����ֵFLP֡��.���Ϊ0��ʾת��ʧ��
int UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen, uint8_t* frame, int frameSize);

// UtzFlpFrameToBytes FLP֡ת��Ϊ�ֽ���.�ֽ�����FLP֡����������
// ����ת������ֽ�������.�����0��ʾת��ʧ��
int UtzFlpFrameToBytes(uint8_t* frame, int frameLen, uint8_t* data, int dataSize);

#endif
