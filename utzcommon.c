// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// 通用模块
// Authors: jdh99 <jdh821@163.com>

#include "utzcommon.h"
#include "utznlv1.h"
#include "tzbox.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 内存管理id
static int mid = -1;

// UtzGetMid 读取内存id
int UtzGetMid(void) {
    if (mid == -1) {
        mid = TZMallocRegister(0, UTZ_TAG, UTZ_MALLOC_SIZE);
        if (mid == -1) {
            LE(UTZ_TAG, "malloc register failed!");
        }
    }
    return mid;
}

// BytesToIA 从字节流中取出IA地址.字节流是大端
// 字节流长度必须保证大于IA_LEN
uint64_t UtzBytesToIA(uint8_t* data) {
    uint64_t ia = 0;
    UtzMemcpyReverse((uint8_t*)&ia, data, UTZ_IA_LEN);
    return ia;
}

// IAToBytes 将IA地址转换为字节流.字节流是大端
void UtzIAToBytes(uint64_t ia, uint8_t* data) {
    UtzMemcpyReverse(data, (uint8_t*)&ia, UTZ_IA_LEN);
}

// UtzMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

// GetNextHeadLen 得到下一头部字节数
// 注意:下一头部不能是正文头部
// bytes是帧的完整字节流,size是帧的总字节数.offset是下一头部的偏移量
// 返回值是下一头部字节数.如果是0表示解析失败
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

// UtzIAStrToHex IA地址字符串转整型
bool UtzIAStrToHex(const char* src, uint64_t* dst) {
    uint8_t dbuf[8];
    uint8_t* datap = dbuf;
    uint8_t* dc = NULL;
    const char* sp;
    char* np;  
    int mask = 0;
    uint64_t res;
    uint8_t* resp = (uint8_t*)&res;
    uint32_t data;

    if (src == NULL) {
        return false;
    }
    sp = src;
    memset(dbuf, 0, sizeof(dbuf));

    while (1) {
        data = (uint32_t)strtol(sp, &np, 16);
       
        if (sp < np) {
            *datap++ = (data >> 8) & 0xff;
            *datap++ = data & 0xff;
            if (*np == ':') {
                mask = 1;
            }
        } else {           
            if (*np == ':' && mask) {
                dc = datap;
            } else {
                mask = 1;
            }            
        }
        
        if (*np != ':' && *np != '\0') {
           return false;
        }

        if (*np == '\0') {
            break;
        }
        sp = np + 1; 
    }

    int i = 7; 
    datap--;

    if (dc) {
        while (datap >= dc)
            resp[i--] = *datap--;
        while (i >= dc - dbuf)
            resp[i--] = 0;
        while (i >= 0)
            resp[i--] = *datap--;
    } else
        memcpy(resp, dbuf, sizeof(dbuf)); 
    TZBoxMemcpyReverse((uint8_t*)dst, (uint8_t*)&res, sizeof(uint64_t));         

    return true;
}

// UtzIAHexToStr IA地址转字符串形式
// type：0：标准输出；1：前导0压缩；2：全0压缩输出
bool UtzIAHexToStr(uint64_t src, char* dst, int type) {
    #define SRCARR_LEN 4

    char str[5];
    uint16_t srcarr[SRCARR_LEN];
    uint16_t *dp;
    int mask = 0;
    if (dst == NULL) {
        return false;
    }

    dst[0] = '\0';
    memcpy((uint8_t*)&srcarr, (uint8_t*)&src, sizeof(uint64_t));                      

    dp = srcarr + (SRCARR_LEN - 1);                         
    switch (type) {
    case 0:
        while (dp >= srcarr) {
            sprintf(str, "%04x", *dp--);
            strcat(dst, str);
            if (dp >= srcarr)
                strcat(dst, ":");
        }    

        break;
    case 1:
        while (dp >= srcarr) {
            sprintf(str, "%x", *dp--);
            strcat(dst, str);
            if (dp >= srcarr)
                strcat(dst, ":");
        }
   
        break;
    case 2:
        while (dp >= srcarr) {
            if (*dp == 0) {
                if (mask < 2) {
                    strcat(dst,":");
                    mask++;
                }
                dp--;
            } else {
                sprintf(str, "%x", *dp--);
                strcat(dst, str);
                if (dp >= srcarr) {
                    strcat(dst, ":");
                    mask = 1;
                }
            }       
        }   

        break;
    default:
        return false;
    }

    return true;
}
