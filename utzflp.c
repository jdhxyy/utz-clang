// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3：Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#include "utzflp.h"
#include "crc16.h"

#include <string.h>

// UtzBytesToFlpFrame 字节流转换为FLP帧
// fixedLen为0表示不是固定长度帧,不需要尾缀
// 返回值FLP帧长.如果为0表示转换失败
int UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen, uint8_t* frame, int frameSize) {
    int frameLen = 2 + dataLen;
    if (isNeedCrc) {
        frameLen += 2;
    }
    if (frameSize < frameLen) {
        return 0;
    }
    memset(frame, 0, (uint64_t)frameLen);

    int suffixLen = 0;
    if (frameLen < fixedLen) {
        suffixLen = fixedLen - frameLen;
        if (suffixLen > UTZ_FLP_SUFFIX_LEN_MAX) {
            suffixLen = UTZ_FLP_SUFFIX_LEN_MAX;
        }
    }

    // 尾缀长度
    uint16_t suffixLenValue = (uint16_t)suffixLen;
    if (isNeedCrc) {
        suffixLenValue |= 0x8000;
    }
    int j = 0;
    frame[j++] = (uint8_t)(suffixLenValue >> 8);
    frame[j++] = (uint8_t)(suffixLenValue);
    // CRC校验
    if (isNeedCrc) {
        uint16_t crc = Crc16Checksum(data, dataLen);
        frame[j++] = (uint8_t)(crc >> 8);
        frame[j++] = (uint8_t)(crc);
    }
    // 正文
    memcpy(frame + j, data, (uint64_t)dataLen);
    j += dataLen;
    // 尾缀
    j += suffixLen;
    return j;
}

// UtzFlpFrameToBytes FLP帧转换为字节流.字节流是FLP帧的数据正文
// 返回转换后的字节流长度.如果是0表示转换失败
int UtzFlpFrameToBytes(uint8_t* frame, int frameLen, uint8_t* data, int dataSize) {
    if (frameLen < 2) {
        return 0;
    }

    uint16_t suffixLenValue = (uint16_t)((frame[0] << 8) + frame[1]);
    int suffixLen = (int)(suffixLenValue & 0x7FFF);
    bool isNeedCrc = (suffixLenValue >> 15) == 0x1;

    // 判断帧最小长度是否正确
    int calcFrameMinSize = suffixLen + 2;
    if (isNeedCrc) {
        calcFrameMinSize = suffixLen + 4;
    }
    if (frameLen < calcFrameMinSize) {
        return 0;
    }

    int dataLen = 0;
    if (isNeedCrc) {
        uint16_t crcGet = (uint16_t)((frame[2] << 8) + frame[3]);
        uint16_t crcCalc = Crc16Checksum(frame + 4, frameLen - 4 - suffixLen);
        if (crcGet != crcCalc) {
            return 0;
        }

        dataLen = frameLen - 4 - suffixLen;
        if (dataSize < dataLen) {
            return 0;
        }
        memcpy(data, frame + 4, (uint64_t)dataLen);
    } else {
        dataLen = frameLen - 2 - suffixLen;
        if (dataSize < dataLen) {
            return 0;
        }
        memcpy(data, frame + 2, (uint64_t)(frameLen - 2 - suffixLen));
    }
    return dataLen;
}
