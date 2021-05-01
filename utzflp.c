// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3��Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#include "utzflp.h"
#include "utzcommon.h"

#include "crc16.h"
#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToFlpFrame �ֽ���ת��ΪFLP֡
// fixedLenΪ0��ʾ���ǹ̶�����֡,����Ҫβ׺
// ����ֵFLP֡.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
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

    // β׺����
    uint16_t suffixLenValue = (uint16_t)suffixLen;
    if (isNeedCrc) {
        suffixLenValue |= 0x8000;
    }
    int j = 0;
    frame->buf[j++] = (uint8_t)(suffixLenValue >> 8);
    frame->buf[j++] = (uint8_t)(suffixLenValue);
    // CRCУ��
    if (isNeedCrc) {
        uint16_t crc = Crc16Checksum(data, dataLen);
        frame->buf[j++] = (uint8_t)(crc >> 8);
        frame->buf[j++] = (uint8_t)(crc);
    }
    // ����
    memcpy(frame->buf + j, data, (uint64_t)dataLen);
    j += dataLen;
    // β׺
    j += suffixLen;

    frame->len = j;
    return frame;
}

// UtzFlpFrameToBytes FLP֡ת��Ϊ�ֽ���.�ֽ�����FLP֡����������
// �����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzFlpFrameToBytes(uint8_t* frame, int frameLen) {
    if (frameLen < 2) {
        return NULL;
    }

    uint16_t suffixLenValue = (uint16_t)((frame[0] << 8) + frame[1]);
    int suffixLen = (int)(suffixLenValue & 0x7FFF);
    bool isNeedCrc = (suffixLenValue >> 15) == 0x1;

    // �ж�֡��С�����Ƿ���ȷ
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
