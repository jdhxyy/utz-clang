// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 3��Fixed Length Transfer Protocol(FLP)
// Authors: jdh99 <jdh821@163.com>

#include "utzflp.h"
#include "crc16.h"

#include <string.h>

// UtzBytesToFlpFrame �ֽ���ת��ΪFLP֡
// fixedLenΪ0��ʾ���ǹ̶�����֡,����Ҫβ׺
// ����ֵFLP֡��.���Ϊ0��ʾת��ʧ��
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

    // β׺����
    uint16_t suffixLenValue = (uint16_t)suffixLen;
    if (isNeedCrc) {
        suffixLenValue |= 0x8000;
    }
    int j = 0;
    frame[j++] = (uint8_t)(suffixLenValue >> 8);
    frame[j++] = (uint8_t)(suffixLenValue);
    // CRCУ��
    if (isNeedCrc) {
        uint16_t crc = Crc16Checksum(data, dataLen);
        frame[j++] = (uint8_t)(crc >> 8);
        frame[j++] = (uint8_t)(crc);
    }
    // ����
    memcpy(frame + j, data, (uint64_t)dataLen);
    j += dataLen;
    // β׺
    j += suffixLen;
    return j;
}

// UtzFlpFrameToBytes FLP֡ת��Ϊ�ֽ���.�ֽ�����FLP֡����������
// ����ת������ֽ�������.�����0��ʾת��ʧ��
int UtzFlpFrameToBytes(uint8_t* frame, int frameLen, uint8_t* data, int dataSize) {
    if (frameLen < 2) {
        return 0;
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
