// BlockCompression.cpp: 定義應用程式的進入點。
//

#include "BlockCompression.h"

char* GetVersion() {
	return "1.2.8.zlib-ng";
}

size_t QuickLzCompress(const void* source, char* destination, size_t size, QuickLZ::qlz_state_compress* state) {
	return QuickLZ::qlz_compress(source, destination, size, state);
}

size_t QuickLzDecompress(const char* source, void* destination, QuickLZ::qlz_state_decompress* state) {
	return QuickLZ::qlz_decompress(source, destination, state);
}

size_t ZSTD_compress(void* dst, size_t dstCapacity, const void* src, size_t srcSize, int compressionLevel) {
	return zstd::ZSTD_compress(dst, dstCapacity, src, srcSize, compressionLevel);
}

size_t ZSTD_decompress(void* dst, size_t dstCapacity, const void* src, size_t compressedSize)
{
	return zstd::ZSTD_decompress(dst, dstCapacity, src, compressedSize);
}

unsigned long long ZSTD_getDecompressedSize(const void* src, size_t srcSize) {
	return zstd::ZSTD_getDecompressedSize(src, srcSize);
}

int bgzf_compress(void* dst, size_t* dlen, const void* src, size_t slen, int level) {
	return htslib::bgzf_compress(dst, dlen, src, slen, level);
}

int bgzf_decompress(void* dst, size_t* dlen, const void* src, size_t slen) {
	return htslib::bgzf_compress(dst, dlen, src, slen, 0);
}