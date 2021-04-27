// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3��Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_FLP_H
#define UTZ_FLP_H

#include "tztype.h"

// �汾
#define UTZ_FLP_VERSION_NAME "1.2"

// ���β׺����
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToFlpFrame �ֽ���ת��ΪFLP֡
// fixedLenΪ0��ʾ���ǹ̶�����֡,����Ҫβ׺
// ����ֵFLP֡.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen);

// UtzFlpFrameToBytes FLP֡ת��Ϊ�ֽ���.�ֽ�����FLP֡����������
// �����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzFlpFrameToBytes(uint8_t* frame, int frameLen);

#endif
