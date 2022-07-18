// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 27��TZ-STAR������ϵͳ���
// Ad Hoc Newwork Control Message Protocol(ADHOCCMP):���������Ʊ���Э��
// Authors: jdh99 <jdh821@163.com>

#include "utz.h"

// UtzBytesToAdhoccHeader �ֽ���ת��Ϊ����������ͷ��
// ����ͷ���Լ�ͷ���ֽ���.�ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToAdhoccHeader(uint8_t* data, int dataLen, UtzAdhoccHeader* header) {
    // ͷ�����ݱ�������
    if (dataLen < HEADER_ADHOCC_LEN) {
        return 0;
    }

    int j = 0;
    header->NextHead = data[j++];
    header->ControlWord.value = data[j++];
    header->PanIA = UtzBytesToIA(data + j);
    j += 4;
    header->SrcRelayIA = UtzBytesToIA(data + j);
    j += 4;
    header->DstRelayIA = UtzBytesToIA(data + j);
    j += 4;
    header->AgingTime = data[j++];
    return j;
}

// UtzADHOCCHeaderToBytes ����������ͷ��ת��Ϊ�ֽ���.ת����洢��bytes��
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzAdhoccHeaderToBytes(UtzAdhoccHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < HEADER_ADHOCC_LEN) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    UtzMemcpyReverse(data + j, (uint8_t*)&(header->PanIA), UTZ_IA_LEN); j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t*)&(header->SrcRelayIA), UTZ_IA_LEN); j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t*)&(header->DstRelayIA), UTZ_IA_LEN); j += UTZ_IA_LEN;
    return j;
}

// UtzGetAdhoccIndex ��ȡ������֡���
uint8_t UtzGetAdhoccIndex(void) {
    static uint8_t adhoccIndex = 0;
    adhoccIndex++;
    if (adhoccIndex > 0xf) {
        adhoccIndex = 0;
    }
    return adhoccIndex;
}

// UtzByteToAgingTime �ֽ�ת��Ϊ�ϻ�ʱ��
// �ϻ�ʱ�䵥λ:s
int UtzByteToAgingTime(uint8_t byte) {
    if (byte <= 0xf) {
        return byte;
    }
    if (byte <= 0x7f) {
        return (byte - 0xf) * 60 + 0xf;
    }
    return (byte - 0x7f) * 900 + (0x7f - 0xf) * 60 + 0xf;
}

// UtzAgingTimeToByte �ϻ�ʱ��ת��Ϊ�ֽ�
// �ϻ�ʱ�䵥λ:s
uint8_t UtzAgingTimeToByte(int agingTime) {
    if (agingTime < 0) {
        return 0;
    }

    int value = 0;
    int delta = agingTime - (0x7f - 0xf) * 60 - 0xf;
    if (delta > 0) {
        value += delta / 900;
        agingTime -= delta;
    }
    delta = agingTime - 0xf;
    if (delta > 0) {
        value += delta / 60;
        agingTime -= delta;
    }
    value += agingTime;
    if (value > 0xff) {
        return 0xff;
    } else {
        return value & 0xff;
    }
}
