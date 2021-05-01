// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3：Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#include "utzflp.h"
#include "utzcommon.h"

#include "crc16.h"
#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToFlpFrame 字节流转换为FLP帧
// fixedLen为0表示不是固定长度帧,不需要尾缀
// 返回值FLP帧.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzBytesToFlpFrame(uint8_t* data, int dataLen, bool isNeedCrc, int fixedLen) {
    int frameSize = (int)sizeof(TZBufferDynamic) + dataLen + 4;
    if (fixedLen > dataLen) {
        frameSize += fixedLen - dataLen;
    }
    TZBufferDynamic* frame = (TZBufferDynamic*)TZMalloc(UtzGetMid(), frameSize);
    if (frame == NULL) {
        LE(UTZ_TAG, "bytes to flp frame failed!malloc failed!");
        return NULL;
    }

    int frameLen = 2 + dataLen;
    if (isNeedCrc) {
        frameLen += 2;
    }

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
    frame->buf[j++] = (uint8_t)(suffixLenValue >> 8);
    frame->buf[j++] = (uint8_t)(suffixLenValue);
    // CRC校验
    if (isNeedCrc) {
        uint16_t crc = Crc16Checksum(data, dataLen);
        frame->buf[j++] = (uint8_t)(crc >> 8);
        frame->buf[j++] = (uint8_t)(crc);
    }
    // 正文
    memcpy(frame->buf + j, data, (uint64_t)dataLen);
    j += dataLen;
    // 尾缀
    j += suffixLen;

    frame->len = j;
    return frame;
}

// UtzFlpFrameToBytes FLP帧转换为字节流.字节流是FLP帧的数据正文
// 返回字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzFlpFrameToBytes(uint8_t* frame, int frameLen) {
    if (frameLen < 2) {
        return NULL;
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
        return NULL;
    }

    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), (int)sizeof(TZBufferDynamic) + frameLen);
    if (data == NULL) {
        LE(UTZ_TAG, "flp frame to bytes failed!malloc failed!");
        return NULL;
    }

    if (isNeedCrc) {
        uint16_t crcGet = (uint16_t)((frame[2] << 8) + frame[3]);
        uint16_t crcCalc = Crc16Checksum(frame + 4, frameLen - 4 - suffixLen);
        if (crcGet != crcCalc) {
            return 0;
        }

        data->len = frameLen - 4 - suffixLen;
        memcpy(data->buf, frame + 4, (uint64_t)data->len);
    } else {
        data->len = frameLen - 2 - suffixLen;
        memcpy(data->buf, frame + 2, (uint64_t)(frameLen - 2 - suffixLen));
    }
    return data;
}
