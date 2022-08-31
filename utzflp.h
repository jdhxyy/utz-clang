// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3：Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_FLP_H
#define UTZ_FLP_H

#include "tztype.h"

// 版本
#define UTZ_FLP_VERSION_NAME "1.2"

// 最大尾缀长度
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToFlpFrame 字节流转换为FLP帧
// fixedLen为0表示不是固定长度帧,不需要尾缀
// 返回值FLP帧.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen);

// UtzFlpFrameToBytes FLP帧转换为字节流.字节流是FLP帧的数据正文
// 返回字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzFlpFrameToBytes(uint8_t* frame, int frameLen);

#endif
