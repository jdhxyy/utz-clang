#include <stdio.h>
#include "utz.h"
#include "scunit.h"
#include "tzmalloc.h"

static int mid = -1;

static void case1(void);
static void case2(void);
static void case3(void);
static void case4(void);
static void case5(void);
static void case6(void);

int main() {
    TZMallocLoad(0, 10, 1024, malloc(1024));
    mid = TZMallocRegister(0, "utz", 1024);
    UtzLoad(mid);

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
    uint8_t data1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint64_t ia = UtzBytesToIA(data1);
    ScunitAssert(ia == 0x102030405060708, "1");

    uint8_t data2[UTZ_IA_LEN] = {0};
    UtzIAToBytes(ia, data2);
    for (int i = 0; i < UTZ_IA_LEN; i++) {
        ScunitAssert(data2[i] == data1[i], "2");
    }
}

static void case2(void) {
    UtzStandardHeader header1;
    header1.Version = UTZ_NLV1_PROTOCOL_VERSION;
    header1.FrameIndex = 5;
    header1.PayloadLen = 6;
    header1.NextHead = 7;
    header1.HopsLimit = 8;
    header1.SrcIA = 0x1234567812345678;
    header1.DstIA = 0x8765432187654321;

    uint8_t data1[100] = {0};
    int num = UtzStandardHeaderToBytes(&header1, data1, 100);
    ScunitAssert(num == UTZ_NLV1_HEAD_LEN, "1");

    // 转换后字节流:01 05 00 06 07 08 12 34 56 78 12 34 56 78 87 65 43 21 87 65 43 21
    uint8_t data2[] = {0x01, 0x05, 0x00, 0x06, 0x07, 0x08, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x87, 0x65, 0x43, 0x21, 0x87, 0x65, 0x43, 0x21};
    for (int i = 0; i < (int)sizeof(data2); i++) {
         ScunitAssert(data2[i] == data1[i], "2");
    }

    UtzStandardHeader header2;
    num = UtzBytesToStandardHeader(data1, (int)sizeof(data2), &header2);
    ScunitAssert(num == UTZ_NLV1_HEAD_LEN, "3");
    ScunitAssert(header2.Version == header1.Version, "4");
    ScunitAssert(header2.FrameIndex == header1.FrameIndex, "4");
    ScunitAssert(header2.PayloadLen == header1.PayloadLen, "4");
    ScunitAssert(header2.NextHead == header1.NextHead, "4");
    ScunitAssert(header2.HopsLimit == header1.HopsLimit, "4");
    ScunitAssert(header2.SrcIA == header1.SrcIA, "4");
    ScunitAssert(header2.DstIA == header1.DstIA, "4");
}

static void case3(void) {
    UtzRouteHeader* header1 = TZMalloc(mid, sizeof(UtzRouteHeader) + UTZ_IA_LEN * 3);
    header1->NextHead = 2;
    header1->RouteNum = 3;
    header1->IsStrict = true;
    header1->IAList[0] = 0x1234567812345677;
    header1->IAList[1] = 0x1234567812345678;
    header1->IAList[2] = 0x1234567812345679;

    uint8_t data1[100] = {0};
    int num = UtzRouteHeaderToBytes(header1, data1, 100);
    ScunitAssert(num == 27, "1");

    // 转换后的字节流:02 19 83 12 34 56 78 12 34 56 77 12 34 56 78 12 34 56 78 12 34 56 78 12 34 56 79
    uint8_t data2[] = {0x02, 0x19, 0x83, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x77, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x79};
    for (int i = 0; i < (int)sizeof(data2); i++) {
         ScunitAssert(data2[i] == data1[i], "2");
    }

    UtzRouteHeader* header2 = UtzBytesToRouteHeader(data1, 100, &num);
    ScunitAssert(num == 27, "3");
    ScunitAssert(header2->NextHead == header1->NextHead, "4");
    ScunitAssert(header2->RouteNum == header1->RouteNum, "4");
    ScunitAssert(header2->IsStrict == header1->IsStrict, "4");
    ScunitAssert(header2->IAList[0] == header1->IAList[0], "4");
    ScunitAssert(header2->IAList[1] == header1->IAList[1], "4");
    ScunitAssert(header2->IAList[2] == header1->IAList[2], "4");

    TZFree(header1);
    TZFree(header2);
}

static void case4(void) {
    uint8_t data[] = {1, 2, 3, 4, 5};
    uint8_t frame1[100] = {0};
    int num = UtzBytesToFlpFrame(data, 5, true, 15, frame1, 100);
    ScunitAssert(num == 15, "1");

    // 转换后的字节流:80 06 2a bb 01 02 03 04 05 00 00 00 00 00 00
    uint8_t frame2[] = {0x80, 0x06, 0x2a, 0xbb, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < (int)sizeof(frame2); i++) {
         ScunitAssert(frame2[i] == frame1[i], "2");
    }

    uint8_t frame3[100] = {0};
    num = UtzBytesToFlpFrame(data, 5, false, 15, frame3, 100);
    ScunitAssert(num == 15, "3");

    // 转换后的字节流:00 08 01 02 03 04 05 00 00 00 00 00 00 00 00
    uint8_t frame4[] = {0x00, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < (int)sizeof(frame2); i++) {
         ScunitAssert(frame4[i] == frame3[i], "4");
    }
}

static void case5(void) {
    // 多加1为了最后是'\0'是字符串
    UtzSimpleSecurityHeader* header1 = TZMalloc(mid, sizeof(UtzSimpleSecurityHeader) + 6);
    header1->NextHead = 5;
    memcpy(header1->Pwd, "jdh99", 5);
    header1->PwdLen = 5;

    uint8_t data1[100] = {0};
    int num = UtzSimpleSecurityHeaderToBytes(header1, data1, 100);
    ScunitAssert(num == 7, "1");

    // 转换后的字节流:05 05 6a 64 68 39 39
    uint8_t data2[] = {0x05, 0x05, 0x6a, 0x64, 0x68, 0x39, 0x39};
    for (int i = 0; i < (int)sizeof(data2); i++) {
         ScunitAssert(data2[i] == data1[i], "2");
    }

    UtzSimpleSecurityHeader* header2 = UtzBytesToSimpleSecurityHeader(data1, 100, &num);
    ScunitAssert(num == 7, "3");
    ScunitAssert(header2->NextHead == header1->NextHead, "4");
    ScunitAssert(header2->PwdLen == header1->PwdLen, "4");
    ScunitAssert(strcmp((char*)header2->Pwd, (char*)header1->Pwd) == 0, "4");

    TZFree(header1);
    TZFree(header2);
}

static void case6(void) {
    uint64_t ia = 0;
    bool result = UtzIAStrToHex("2141::2", &ia);
    ScunitAssert(result == true, "1");
    ScunitAssert(ia == 0x2141000000000002, "1");

    result = UtzIAStrToHex("2141:0:0:2", &ia);
    ScunitAssert(result == true, "2");
    ScunitAssert(ia == 0x2141000000000002, "2");

    char str[32] = {0};
    UtzIAHexToStr(0x2141000000000002, str, 0);
    ScunitAssert(strcmp(str, "2141:0000:0000:0002") == 0, "3");
    UtzIAHexToStr(0x2141000000000002, str, 1);
    ScunitAssert(strcmp(str, "2141:0:0:2") == 0, "3");
    UtzIAHexToStr(0x2141000000000002, str, 2);
    ScunitAssert(strcmp(str, "2141::2") == 0, "3");
}
