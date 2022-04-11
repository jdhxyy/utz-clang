#include <stdio.h>
#include "utz.h"
#include "scunit.h"
#include "tzmalloc.h"
#include "tztype.h"

static int mid = -1;

static void case1(void);

static void case2(void);
static void printHex(uint8_t* data, int dataLen);

static void case3(void);
static void case4(void);
static void case5(void);
static void case6(void);

int main() {
    TZMallocLoad(0, 10, 1024, malloc(1024));
    mid = TZMallocRegister(0, "test", 1024);

    ScunitLoad((ScunitPrintFunc)printf);
    ScunitAddSuite("test_utz");
    ScunitAddTest("case1", case1);
    ScunitAddTest("case2", case2);
    ScunitAddTest("case3", case3);
    ScunitAddTest("case4", case4);
    ScunitAddTest("case5", case5);
    ScunitAddTest("case6", case6);
    return 0;
}

static void case1(void) {
    uint8_t data1[] = {1, 2, 3, 4};
    uint32_t ia = UtzBytesToIA(data1);
    ScunitAssert(ia == 0x1020304, "1");

    uint8_t data2[UTZ_IA_LEN] = {0};
    UtzIAToBytes(ia, data2);
    for (int i = 0; i < UTZ_IA_LEN; i++) {
        ScunitAssert(data2[i] == data1[i], "2");
    }
}

static void case2(void) {
    UtzStandardHeader header1;
    header1.Version = UTZ_NLP_PROTOCOL_VERSION;
    header1.PayloadLen = 6;
    header1.NextHead = 7;
    header1.SrcIA = 0x12345678;
    header1.DstIA = 0x87654321;

    uint8_t data1[100] = {0};
    int num = UtzStandardHeaderToBytes(&header1, data1, 100);
    ScunitAssert(num == UTZ_NLP_HEAD_LEN, "1");

//    printHex(data1, num);

    // 转换后字节流
    uint8_t data2[] = {0x20, 0x06, 0x07, 0x12, 0x34, 0x56, 0x78, 0x87, 0x65, 0x43, 0x21};
    for (int i = 0; i < (int)sizeof(data2); i++) {
         ScunitAssert(data2[i] == data1[i], "2");
    }

    UtzStandardHeader header2;
    num = UtzBytesToStandardHeader(data1, (int)sizeof(data2), &header2);
    ScunitAssert(num == UTZ_NLP_HEAD_LEN, "3");
    ScunitAssert(header2.Version == header1.Version, "4");
    ScunitAssert(header2.PayloadLen == header1.PayloadLen, "4");
    ScunitAssert(header2.NextHead == header1.NextHead, "4");
    ScunitAssert(header2.SrcIA == header1.SrcIA, "4");
    ScunitAssert(header2.DstIA == header1.DstIA, "4");
}

static void printHex(uint8_t* data, int dataLen) {
    for (int i = 0; i < dataLen; i++) {
        printf("0x%02x, ", data[i]);
    }
    printf("\n");
}

static void case3(void) {
    UtzRouteHeader header1;
    header1.NextHead = 2;
    header1.IA = 0x12345678;

    TZBuffer buffer;
    buffer.len = UtzRouteHeaderToBytes(&header1, buffer.buf, TZ_BUFFER_LEN);
    ScunitAssert(buffer.len == 5, "1");

//    printHex(buffer.buf, buffer.len);

    // 转换后的字节流
    uint8_t data2[] = {0x02, 0x12, 0x34, 0x56, 0x78};
    for (int i = 0; i < (int)sizeof(data2); i++) {
        ScunitAssert(data2[i] == buffer.buf[i], "2");
    }

    UtzRouteHeader header2;
    int offset = UtzBytesToRouteHeader(buffer.buf, buffer.len, &header2);
    ScunitAssert(offset == 5, "2");

    ScunitAssert(header2.NextHead == header1.NextHead, "4");
    ScunitAssert(header2.IA == header1.IA, "4");
}

static void case4(void) {
    uint8_t data[] = {1, 2, 3, 4, 5};
    TZBufferDynamic* frame1 = UtzBytesToFlpFrame(data, 5, true, 15);
    ScunitAssert(frame1->len == 15, "1");

    // 转换后的字节流:80 06 2a bb 01 02 03 04 05 00 00 00 00 00 00
    uint8_t frame2[] = {0x80, 0x06, 0x2a, 0xbb, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < (int)sizeof(frame2); i++) {
        ScunitAssert(frame2[i] == frame1->buf[i], "2");
    }

    TZBufferDynamic* frame3 = UtzBytesToFlpFrame(data, 5, false, 15);
    ScunitAssert(frame3->len == 15, "3");

    // 转换后的字节流:00 08 01 02 03 04 05 00 00 00 00 00 00 00 00
    uint8_t frame4[] = {0x00, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < (int)sizeof(frame2); i++) {
        ScunitAssert(frame4[i] == frame3->buf[i], "4");
    }

    TZFree(frame1);
    TZFree(frame3);
}

static void case5(void) {
    // 多加1为了最后是'\0'是字符串
    UtzSimpleSecurityHeader* header1 = TZMalloc(mid, sizeof(UtzSimpleSecurityHeader) + 6);
    header1->NextHead = 5;
    memcpy(header1->Pwd, "jdh99", 5);
    header1->PwdLen = 5;

    TZBufferDynamic* data1 = UtzSimpleSecurityHeaderToBytes(header1);
    ScunitAssert(data1->len == 7, "1");

    // 转换后的字节流:05 05 6a 64 68 39 39
    uint8_t data2[] = {0x05, 0x05, 0x6a, 0x64, 0x68, 0x39, 0x39};
    for (int i = 0; i < (int)sizeof(data2); i++) {
         ScunitAssert(data2[i] == data1->buf[i], "2");
    }

    int num = 0;
    UtzSimpleSecurityHeader* header2 = UtzBytesToSimpleSecurityHeader(data1->buf, data1->len, &num);
    ScunitAssert(num == 7, "3");
    ScunitAssert(header2->NextHead == header1->NextHead, "4");
    ScunitAssert(header2->PwdLen == header1->PwdLen, "4");
    ScunitAssert(strcmp((char*)header2->Pwd, (char*)header1->Pwd) == 0, "4");

    TZFree(header1);
    TZFree(header2);
    TZFree(data1);
}

static void case6(void) {
    uint8_t data[] = {1, 2, 3, 4, 5};
    TZBufferDynamic* frame1 = UtzBytesToCcpFrame(data, 5, true);
    ScunitAssert(frame1->len == 7, "1");

//    printHex(frame1->buf, frame1->len);

    // 转换后的字节流
    uint8_t frame2[] = {0x2a, 0xbb, 0x01, 0x02, 0x03, 0x04, 0x05};
    for (int i = 0; i < (int)sizeof(frame2); i++) {
        ScunitAssert(frame2[i] == frame1->buf[i], "2");
    }

    TZFree(frame1);
}
