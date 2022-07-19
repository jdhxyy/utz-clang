// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 2��Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_EHP_H
#define UTZ_EHP_H

#include "tztype.h"

// �汾
#define UTZ_EHP_VERSION_NAME "1.2"

// ��չͷ��
// ·��ͷ��
#define UTZ_HEADER_ROUTE 0x1
// ��Ƭͷ��
#define UTZ_HEADER_FRAGMENT 0x2
// ����ͷ��
#define UTZ_HEADER_ENCRYPTION 0x3
// FLP
#define UTZ_HEADER_FLP 0x4
// CMP
#define UTZ_HEADER_CMP 0x5
// WTS
#define UTZ_HEADER_WTS 0x6
// DUP
#define UTZ_HEADER_DUP 0x7
// SFTPA
#define UTZ_HEADER_SFTPA 0x8
// SFTPB
#define UTZ_HEADER_SFTPB 0x9
// STCP
#define UTZ_HEADER_STCP 0xA
// ITCP
#define UTZ_HEADER_ITCP 0xB
// DAP
#define UTZ_HEADER_DAP 0xC
// A��RSSIͷ��
#define UTZ_HEADER_RSSI_A 0xD
// B��RSSIͷ��
#define UTZ_HEADER_RSSI_B 0xE
// A�෢�Ϳ���ͷ��
#define UTZ_HEADER_RADIO_TX_CONTROL_A 0xF
// 125K����RSSIͷ��
#define UTZ_HEADER_EXCITER_RSSI 0x10
// A��TOF��λͷ��
#define UTZ_HEADER_TOF_LOCATION_A 0x11
// A��DW1000����ͷ��
#define UTZ_HEADER_DW1000_RX_A 0x12
// A��DW1000�������ͷ��
#define UTZ_HEADER_DW1000_TX_END_A 0x13
// A������ͷ��
#define UTZ_HEADER_COORDINATE_A 0x14
// ʱ���ͷ��
#define UTZ_HEADER_TIMESTAMP 0x15
// ����ͷ��
#define UTZ_HEADER_AGENT 0x16
// ����������ͷ��
#define UTZ_HEADER_ADHOCC 0x17
// ѹ��ͷ������֡
#define UTZ_HEADER_COMPRESS_COMPLEX 0x18
// ��׼ͷ������֡
#define UTZ_HEADER_STANDARD_COMPLEX 0x19
// ȫ�򵥲���ַ�������������Э��
#define UTZ_HEADER_GUAAP 0x1A
// �̶���ַ��������������Э��
// ���ķ���������Э��
// �򵥰�ȫͷ��
#define UTZ_HEADER_SIMPLE_SECURITY 0x1D
// �����������ͷ��
#define UTZ_HEADER_FIXED_LENGTH_TRANSFER_CONTROL 0x1E
// �м�ͷ��
#define UTZ_HEADER_REPEAT 0x1F
// �ӷ�Ƭͷ��
#define UTZ_HEADER_SUB_FRAGMENT 0x20
// ϵͳ��־Э��
#define UTZ_HEADER_SLP 0x22
// �豸��ͨ��Э��
#define UTZ_HEADER_DCOM 0x23
// �������ն�Э��
#define UTZ_HEADER_ISH 0x24
// CRC16ͨ��Э��
#define UTZ_HEADER_CCP 0x25
// ԭʼ����ͨ��Э��
#define UTZ_HEADER_RP 0x26
// ���������Ʊ���Э��
#define UTZ_HEADER_ADHOCCMP 0x27

#pragma pack(1)

// RouteHeader ·��ͷ���ṹ
typedef struct {    
    uint8_t NextHead;
    // ·�ɵ�ַ
    uint32_t IA;
} UtzRouteHeader;

// SimpleSecurityHeader �򵥰�ȫͷ���ṹ
typedef struct {
    uint8_t NextHead;
    uint8_t PwdLen;
    uint8_t Pwd[];
} UtzSimpleSecurityHeader;

typedef union {
    struct {
        // ƫ����
        uint16_t Offset:15;
        // ���һƬ��ʶ
        uint16_t IsLastPiece:1;
    } bit;
    uint16_t value;
} UtzFragmentOffset;

// UtzFragmentHeader ��Ƭͷ��
typedef struct {
    // ����ͷ��
    uint8_t Head;
    // ��ʶ��
    uint16_t Flag;
    // ��Ƭƫ����
    UtzFragmentOffset Offset;
} UtzFragmentHeader;

#pragma pack()

// UtzBytesToRouteHeader �ֽ���ת��Ϊ·��ͷ��.�ֽ����Ǵ��
// �ֽ���data�������·��ͷ������
// ����ͷ���Լ�ͷ���ֽ���.ͷ��Ϊnil�����ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToRouteHeader(uint8_t* data, int dataLen, UtzRouteHeader* header);

// UtzRouteHeader ·��ͷ��ת��Ϊ�ֽ���
// �ֽ���data�������·��ͷ������
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzRouteHeaderToBytes(UtzRouteHeader* header, uint8_t* data, int dataSize);

// UtzIsPayloadHeader �Ƿ��غ�ͷ��
bool UtzIsPayloadHeader(uint8_t head);

// UtzBytesToSimpleSecurityHeader �ֽ���ת��Ϊ�򵥰�ȫͷ��
// offset��ת�����ֽ����µ�ƫ�Ƶ�ַ.���Ϊ0��ʾת��ʧ��.����Ҫ֪������дNULL
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* offset);

// SimpleSecurityHeaderToBytes �򵥰�ȫͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header);

// UtzSimpleSecurityHeaderDataToBytes �򵥰�ȫͷ������ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzSimpleSecurityHeaderDataToBytes(uint8_t nextHead, char* pwd);

// UtzFragmentHeaderToBytes ��Ƭͷ��ת��Ϊ�ֽ���
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzFragmentHeaderToBytes(UtzFragmentHeader* header, uint8_t* data, int dataSize);

#endif
