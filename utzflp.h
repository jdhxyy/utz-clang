// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3：Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_FLP_H
#define UTZ_FLP_H

#include <stdint.h>
#include <stdbool.h>

// 版本
#define UTZ_FLP_VERSION_NAME "1.2"

// 最大尾缀长度
#define UTZ_FLP_SUFFIX_LEN_MAX 0x7FF

// UtzBytesToFlpFrame 字节流转换为FLP帧
// fixedLen为0表示不是固定长度帧,不需要尾缀
// 返回值FLP帧长.如果为0表示转换失败
int UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen, uint8_t* frame, int frameSize);

// UtzFlpFrameToBytes FLP帧转换为字节流.字节流是FLP帧的数据正文
// 返回转换后的字节流长度.如果是0表示转换失败
int UtzFlpFrameToBytes(uint8_t* frame, int frameLen, uint8_t* data, int dataSize);

#endif
