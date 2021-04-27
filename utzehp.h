// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2��Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_EHP_H
#define UTZ_EHP_H

#include "tztype.h"

// �汾
#define UTZ_EHP_VERSION_NAME "1.1"

// ��չͷ��
// ������ѡ��ͷ��
#define UTZ_HEADER_HOP_BY_HOP_OPTIONS 0x0
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

#pragma pack(1)

// RouteHeader ·��ͷ���ṹ
typedef struct {    
    uint8_t NextHead;
    // ʣ��·����
    uint8_t RouteNum;
    // �Ƿ��ϸ�Դ·��
    bool IsStrict;
    // ·�ɵ�ַ�б�
    uint64_t IAList[];
} UtzRouteHeader;

// SimpleSecurityHeader �򵥰�ȫͷ���ṹ
typedef struct {
	uint8_t NextHead;
    uint8_t PwdLen;
    uint8_t Pwd[];
} UtzSimpleSecurityHeader;

#pragma pack()

// UtzBytesToRouteHeader �ֽ���ת��Ϊ·��ͷ��
// offset��ת�����ֽ����µ�ƫ�Ƶ�ַ.���Ϊ0��ʾת��ʧ��.����Ҫ֪������дNULL
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* offset);

// UtzRouteHeaderToBytes ·��ͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzRouteHeaderToBytes(UtzRouteHeader* header);

// UtzIsPayloadHeader �Ƿ��غ�ͷ��
bool UtzIsPayloadHeader(uint8_t head);

// UtzBytesToSimpleSecurityHeader �ֽ���ת��Ϊ�򵥰�ȫͷ��
// bytesNum�Ƿ��ص�ת��ͷ�����ֽ����ֽ���.���Ϊ0��ʾת��ʧ��
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* bytesNum);

// SimpleSecurityHeaderToBytes �򵥰�ȫͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.���Ϊ0��ʾת��ʧ��
int UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header, uint8_t* data, int dataSize);

#endif
