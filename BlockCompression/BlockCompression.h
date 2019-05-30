// BlockCompression.hpp: 標準系統 include 檔案的 include 檔案，
// 或專案專屬的 Include 檔案。

#pragma once

// 下列 ifdef 區塊是建立巨集的標準方式，讓從 DLL 匯出的過程更簡單。
// 此 DLL 中的所有檔案均使用命令列中定義的 BLOCKCOMPRESSION_EXPORTS 來編譯。
// 此符號不應在其他使用此 DLL 的任何專案中定義
// 這樣一來，原始程式檔中包含此檔案的其他任何專案，
// 都會將 BLOCKCOMPRESSION_API 函式視為從 DLL 匯入，
// 而此 DLL 會將使用此巨集定義的符號視為匯出。
#ifdef BLOCKCOMPRESSION_EXPORTS
	#define BLOCKCOMPRESSION_API __declspec(dllexport)
#else
	#ifdef _MSC_VER
		#define BLOCKCOMPRESSION_API __declspec(dllimport)
	#else
		#define BLOCKCOMPRESSION_API
	#endif
#endif

// TODO: 在此參考您的程式所需的其他標頭。
#include <cstdint>
#include <cstddef>

namespace QuickLZ {
	#include "quicklz.h"
}

namespace zstd {
	#include "zstd.h"
}

namespace htslib {
	#include "htslib/bgzf.h"
}

extern "C" {
	BLOCKCOMPRESSION_API char* GetVersion();
	BLOCKCOMPRESSION_API size_t QuickLzCompress(const void* source, char* destination, size_t size, QuickLZ::qlz_state_compress* state);
	BLOCKCOMPRESSION_API size_t QuickLzDecompress(const char* source, void* destination, QuickLZ::qlz_state_decompress* state);
	BLOCKCOMPRESSION_API size_t qlz_size_decompressed(const char* source);
	BLOCKCOMPRESSION_API size_t ZSTD_compress(void* dst, size_t dstCapacity,
		const void* src, size_t srcSize,
		int compressionLevel);

	BLOCKCOMPRESSION_API size_t ZSTD_decompress(void* dst, size_t dstCapacity,
		const void* src, size_t compressedSize);

	BLOCKCOMPRESSION_API unsigned long long ZSTD_getDecompressedSize(const void* src, size_t srcSize);

	BLOCKCOMPRESSION_API int bgzf_compress(void* dst, size_t* dlen, const void* src, size_t slen, int level);

	BLOCKCOMPRESSION_API int bgzf_decompress(void* dst, size_t* dlen, const void* src, size_t slen);

}