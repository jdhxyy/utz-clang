// Copyright 2022-2022 The jdh99 Authors. All rights reserved.
// CCP：CRC16 CheckSum Protocol
// Authors: jdh99 <jdh821@163.com>

#include "utzccp.h"
#include "utzcommon.h"

#include "crc16.h"
#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToCcpFrame 字节流转换为CCP帧
// 字节流dst必须大于等于srcLen+2
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzBytesToCcpFrame(uint8_t* src, int srcLen, bool isNeedCrc, uint8_t* dst, int dstSize) {
    if (dstSize < srcLen + 2) {
        return 0;
    }

    int j = 0;

    // CRC校验
    uint16_t crc = 0;
    if (isNeedCrc) {
        crc = Crc16Checksum(src, srcLen);
    }
    dst[j++] = (uint8_t)(crc >> 8);
    dst[j++] = (uint8_t)(crc);
    // 正文
    memcpy(dst + j, src, (uint64_t)srcLen);
    j += srcLen;

    return j;
}

// UtzCcpFrameToBytes CCP帧转换为字节流.字节流是CCP帧的数据正文
// 返回字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzCcpFrameToBytes(uint8_t* frame, int frameLen) {
    if (frameLen < 2) {
        return NULL;
    }

    uint16_t crcGet = (uint16_t)((frame[0] << 8) + frame[1]);
    if (crcGet != 0) {
        // 有CRC
        uint16_t crcCalc = Crc16Checksum(frame + 2, frameLen - 2);
        if (crcGet != crcCalc) {
            LE(UTZ_TAG, "ccp frame to bytes failed!crc calc failed:0x%x 0x%x", crcCalc, crcGet);
            return NULL;
        }
    }

    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), (int)sizeof(TZBufferDynamic) + frameLen - 2);
    if (data == NULL) {
        LE(UTZ_TAG, "ccp frame to bytes failed!malloc failed!");
        return NULL;
    }

    data->len = frameLen - 2;
    memcpy(data->buf, frame + 2, (uint64_t)(data->len));
    return data;
}

// UtzCcpFrameIsValid CCP帧是否有效
bool UtzCcpFrameIsValid(uint8_t* frame, int frameLen) {
    if (frameLen < 2) {
        return false;
    }

    uint16_t crcGet = (uint16_t)((frame[0] << 8) + frame[1]);
    if (crcGet != 0) {
        // 有CRC
        uint16_t crcCalc = Crc16Checksum(frame + 2, frameLen - 2);
        if (crcGet != crcCalc) {
            return false;
        }
    }
    return true;
}
