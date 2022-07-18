// Copyright 2022-2022 The jdh99 Authors. All rights reserved.
// CCP��CRC16 CheckSum Protocol
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CCP_H
#define UTZ_CCP_H

#include "tztype.h"

// �汾
#define UTZ_CCP_VERSION_NAME "1.0"

// ���β׺����
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToCcpFrame �ֽ���ת��ΪCCP֡
// �ֽ���dst������ڵ���srcLen+2
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzBytesToCcpFrame(uint8_t* src, int srcLen, bool isNeedCrc, uint8_t* dst, int dstSize);

// UtzCcpFrameToBytes CCP֡ת��Ϊ�ֽ���.�ֽ�����CCP֡����������
// �����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzCcpFrameToBytes(uint8_t* frame, int frameLen);

// UtzCcpFrameIsValid CCP֡�Ƿ���Ч
bool UtzCcpFrameIsValid(uint8_t* frame, int frameLen);

#endif
