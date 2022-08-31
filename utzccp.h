// Copyright 2022-2022 The jdh99 Authors. All rights reserved.
// CCP：CRC16 CheckSum Protocol
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CCP_H
#define UTZ_CCP_H

#include "tztype.h"

// 版本
#define UTZ_CCP_VERSION_NAME "1.0"

// 最大尾缀长度
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToCcpFrame 字节流转换为CCP帧
// 字节流dst必须大于等于srcLen+2
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzBytesToCcpFrame(uint8_t* src, int srcLen, bool isNeedCrc, uint8_t* dst, int dstSize);

// UtzCcpFrameToBytes CCP帧转换为字节流.字节流是CCP帧的数据正文
// 返回字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzCcpFrameToBytes(uint8_t* frame, int frameLen);

// UtzCcpFrameIsValid CCP帧是否有效
bool UtzCcpFrameIsValid(uint8_t* frame, int frameLen);

#endif
