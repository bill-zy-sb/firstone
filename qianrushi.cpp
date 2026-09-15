#include <stdio.h>
#include <stdlib.h>

// 类型定义
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned char BYTE;

// 任务1：定义BITMAPFILEHEADER结构体
typedef struct {
    WORD bfType;        // 位图文件类型，必须为"BM"
    DWORD bfSize;       // 文件大小
    WORD bfReserved1;   // 保留字，必须为0
    WORD bfReserved2;   // 保留字，必须为0
    DWORD bfOffBits;    // 位图数据距文件头的偏移量
} BITMAPFILEHEADER;

// 任务2：定义BITMAPINFOHEADER结构体
typedef struct {
    DWORD biSize;           // 结构体大小
    LONG biWidth;           // 位图宽度
    LONG biHeight;          // 位图高度
    WORD biPlanes;          // 平面数，必须为1
    WORD biBitCount;        // 每像素位数
    DWORD biCompression;    // 压缩类型
    DWORD biSizeImage;      // 位图数据大小
    LONG biXPelsPerMeter;   // 水平分辨率
    LONG biYPelsPerMeter;   // 垂直分辨率
    DWORD biClrUsed;        // 实际使用的颜色数
    DWORD biClrImportant;   // 重要颜色数
} BITMAPINFOHEADER;

// 任务3：C语言文件操作函数说明
// 常用文件操作函数：
// - fopen(const char* filename, const char* mode): 打开文件
// - fclose(FILE* stream): 关闭文件
// - fread(void* ptr, size_t size, size_t count, FILE* stream): 读取文件
// - fwrite(const void* ptr, size_t size, size_t count, FILE* stream): 写入文件
// - fseek(FILE* stream, long offset, int origin): 文件定位
// - ftell(FILE* stream): 获取当前文件位置
// - fgetc(FILE* stream): 读取一个字符
// - fputc(int char, FILE* stream): 写入一个字符
// - fgets(char* str, int num, FILE* stream): 读取一行
// - fprintf(FILE* stream, const char* format, ...): 格式化写入
// - fscanf(FILE* stream, const char* format, ...): 格式化读取

// 任务4：动态内存申请和释放函数
// - malloc(size_t size): 分配指定大小的内存，返回void指针
// - calloc(size_t num, size_t size): 分配num个size大小的内存，初始化为0
// - realloc(void* ptr, size_t size): 重新分配内存
// - free(void* ptr): 释放动态分配的内存

// 任务8：位图反色处理函数
int bmpInvertColor(const char* inputPath, const char* outputPath) {
    FILE* pFile = fopen(inputPath, "rb");
    if (pFile == NULL) {
        printf("无法打开输入文件\n");
        return -1;
    }

    // 任务5：定义BITMAPFILEHEADER结构体指针
    BITMAPFILEHEADER* p_bmpFileHead;

    // 任务6：申请动态内存并赋值给结构体指针
    p_bmpFileHead = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    if (p_bmpFileHead == NULL) {
        printf("内存分配失败\n");
        fclose(pFile);
        return -1;
    }

    BITMAPINFOHEADER* p_bmpInfoHead = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    if (p_bmpInfoHead == NULL) {
        printf("内存分配失败\n");
        free(p_bmpFileHead);
        fclose(pFile);
        return -1;
    }

    // 读取文件头
    fread(p_bmpFileHead, sizeof(BITMAPFILEHEADER), 1, pFile);
    
    // 验证是否为BMP文件
    if (p_bmpFileHead->bfType != 0x4D42) { // "BM"
        printf("不是有效的BMP文件\n");
        free(p_bmpFileHead);
        free(p_bmpInfoHead);
        fclose(pFile);
        return -1;
    }

    // 读取信息头
    fread(p_bmpInfoHead, sizeof(BITMAPINFOHEADER), 1, pFile);

    // 只处理24位真彩色位图
    if (p_bmpInfoHead->biBitCount != 24) {
        printf("仅支持24位真彩色位图\n");
        free(p_bmpFileHead);
        free(p_bmpInfoHead);
        fclose(pFile);
        return -1;
    }

    LONG width = p_bmpInfoHead->biWidth;
    LONG height = p_bmpInfoHead->biHeight;

    // 计算每行的字节数（BMP每行必须是4的倍数）
    int rowSize = (width * 3 + 3) & ~3;
    int totalSize = rowSize * abs(height);

    // 任务7：申请BYTE类型内存
    BYTE* pBuffer = (BYTE*)malloc(totalSize);
    if (pBuffer == NULL) {
        printf("内存分配失败\n");
        free(p_bmpFileHead);
        free(p_bmpInfoHead);
        fclose(pFile);
        return -1;
    }

    // 读取位图数据
    fread(pBuffer, totalSize, 1, pFile);
    fclose(pFile);

    // 反色处理 (255 - B/G/R)
    for (int i = 0; i < totalSize; i += 3) {
        pBuffer[i] = 255 - pBuffer[i];     // B
        pBuffer[i + 1] = 255 - pBuffer[i + 1]; // G
        pBuffer[i + 2] = 255 - pBuffer[i + 2]; // R
    }

    // 打开输出文件
    FILE* pOutFile = fopen(outputPath, "wb");
    if (pOutFile == NULL) {
        printf("无法打开输出文件\n");
        free(p_bmpFileHead);
        free(p_bmpInfoHead);
        free(pBuffer);
        return -1;
    }

    // 写入文件头和信息头
    fwrite(p_bmpFileHead, sizeof(BITMAPFILEHEADER), 1, pOutFile);
    fwrite(p_bmpInfoHead, sizeof(BITMAPINFOHEADER), 1, pOutFile);
    
    // 写入处理后的位图数据
    fwrite(pBuffer, totalSize, 1, pOutFile);

    // 任务7：释放BYTE类型内存
    free(pBuffer);
    free(p_bmpInfoHead);
    free(p_bmpFileHead);
    fclose(pOutFile);

    printf("反色处理完成\n");
    return 0;
}

int main() {
    const char* inputFile = "input.bmp";
    const char* outputFile = "output.bmp";
    
    printf("位图反色处理程序\n");
    printf("输入文件: %s\n", inputFile);
    printf("输出文件: %s\n", outputFile);
    
    int result = bmpInvertColor(inputFile, outputFile);
    
    if (result == 0) {
        printf("处理成功！\n");
    } else {
        printf("处理失败！\n");
    }

    return 0;
}
