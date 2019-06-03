// BlockCompression.cpp: 定義應用程式的進入點。
//

#include "BlockCompression.h"

char* GetVersion() {
	return "1.2.8.zlib-ng";
}

size_t QuickLzCompress(char* source, int sourceLen, char* destination, int destinationLen) {
	qlz_state_compress* state_compress = (qlz_state_compress*)malloc(sizeof(qlz_state_compress));
	return qlz_compress(source, destination, sourceLen, state_compress);
}

size_t QuickLzDecompress(char* source, char* destination, int destinationLen) {
	qlz_state_decompress* state_decompress = (qlz_state_decompress*)malloc(sizeof(qlz_state_decompress));
	return qlz_decompress(source, destination, state_decompress);
}

int bgzf_decompress(void* dst, size_t* dlen, const void* src, size_t slen) {
	return bgzf_compress(dst, dlen, src, slen, 0);
}