// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 4��Control Message Protocol(CMP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CMP_H
#define UTZ_CMP_H

#include <stdint.h>

// �汾
#define UTZ_CMP_VERSION_NAME "1.1"

// ��Ϣ����
// ����ӻ�
#define UTZ_CMP_MSG_TYPE_REQUEST_SLAVE_ROUTER 0x88
// ����ӻ�
#define UTZ_CMP_MSG_TYPE_ASSIGN_SLAVE_ROUTER 0x89
// ���Ӹ�·��
#define UTZ_CMP_MSG_TYPE_CONNECT_PARENT_ROUTER 0x8A
// ȷ�����Ӹ�·��
#define UTZ_CMP_MSG_TYPE_ACK_CONNECT_PARENT_ROUTER 0x8B

#endif
