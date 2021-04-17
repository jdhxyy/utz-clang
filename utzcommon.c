// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// ͨ��ģ��
// Authors: jdh99 <jdh821@163.com>

#include "utzcommon.h"
#include "utznlv1.h"

// BytesToIA ���ֽ�����ȡ��IA��ַ.�ֽ����Ǵ��
// �ֽ������ȱ��뱣֤����IA_LEN
uint64_t UtzBytesToIA(uint8_t* data) {
    uint64_t ia = 0;
    UtzMemcpyReverse((uint8_t*)&ia, data, UTZ_IA_LEN);
    return ia;
}

// IAToBytes ��IA��ַת��Ϊ�ֽ���.�ֽ����Ǵ��
void UtzIAToBytes(uint64_t ia, uint8_t* data) {
    UtzMemcpyReverse(data, (uint8_t*)&ia, UTZ_IA_LEN);
}

// UtzMemcpyReverse ��ת����.����srcΪС�˴洢.����ת��Ϊ��˴洢��dst��
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

// GetNextHeadLen �õ���һͷ���ֽ���
// ע��:��һͷ������������ͷ��
// bytes��֡�������ֽ���,size��֡�����ֽ���.offset����һͷ����ƫ����
// ����ֵ����һͷ���ֽ���.�����0��ʾ����ʧ��
int UtzGetNextHeadLen(uint8_t* bytes, int size, int offset) {
    if (size < offset+2) {
        return 0;
    }
    int nextHeadLen = bytes[offset+1] + 2;
    if (size < offset+nextHeadLen) {
        return 0;
    }
    return nextHeadLen;
}

// UtzHtons 2�ֽ�������ת��Ϊ������
uint16_t UtzHtons(uint16_t n) {
    return (uint16_t)(((n & 0xff) << 8) | ((n & 0xff00) >> 8));
}

// UtzNtohs 2�ֽ�������ת��Ϊ������
uint16_t UtzNtohs(uint16_t n) {
    return UtzHtons(n);
}

// UtzHtonl 4�ֽ�������ת��Ϊ������
uint32_t UtzHtonl(uint32_t n) {
    return ((n & 0xff) << 24) |
        ((n & 0xff00) << 8) |
        ((n & 0xff0000UL) >> 8) |
        ((n & 0xff000000UL) >> 24);
}

// UtzNtohl 4�ֽ�������ת��Ϊ������
uint32_t UtzNtohl(uint32_t n) {
    return UtzHtonl(n);
}

// UtzHtonll 8�ֽ�������ת��Ϊ������
uint64_t UtzHtonll(uint64_t n) {
    return ((n & 0xff) << 56) |
        ((n & 0xff00) << 40) |
        ((n & 0xff0000) << 24) |
        ((n & 0xff000000) << 8) |
        ((n & 0xff00000000ULL) >> 8) |
        ((n & 0xff0000000000ULL) >> 24) |
        ((n & 0xff000000000000ULL) >> 40) |
        ((n & 0xff00000000000000ULL) >> 56);
}

// UtzNtohll 8�ֽ�������ת��Ϊ������
uint64_t UtzNtohll(uint64_t n) {
    return UtzHtonll(n);
}
