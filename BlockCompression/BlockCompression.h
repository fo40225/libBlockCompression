// BlockCompression.hpp: 標準系統 include 檔案的 include 檔案，
// 或專案專屬的 Include 檔案。

#pragma once

// 下列 ifdef 區塊是建立巨集的標準方式，讓從 DLL 匯出的過程更簡單。
// 此 DLL 中的所有檔案均使用命令列中定義的 BLOCKCOMPRESSION_EXPORTS 來編譯。
// 此符號不應在其他使用此 DLL 的任何專案中定義
// 這樣一來，原始程式檔中包含此檔案的其他任何專案，
// 都會將 BLOCKCOMPRESSION_API 函式視為從 DLL 匯入，
// 而此 DLL 會將使用此巨集定義的符號視為匯出。
//#ifdef BLOCKCOMPRESSION_EXPORTS
//	#define BLOCKCOMPRESSION_API __declspec(dllexport)
//#else
//	#define BLOCKCOMPRESSION_API __declspec(dllimport)
//#endif

// https://gcc.gnu.org/wiki/Visibility
#if defined _WIN32
	#ifdef BlockCompression_EXPORTS
		#ifdef __GNUC__
			#define BLOCKCOMPRESSION_API __attribute__ ((dllexport))
		#else
			#define BLOCKCOMPRESSION_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
		#endif
	#else
		#ifdef __GNUC__
			#define BLOCKCOMPRESSION_API __attribute__ ((dllimport))
		#else
			#define BLOCKCOMPRESSION_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
		#endif
	#endif
#else
	#if __GNUC__ >= 4
		#define BLOCKCOMPRESSION_API __attribute__ ((visibility ("default")))
	#else
		#define BLOCKCOMPRESSION_API
	#endif
#endif

// TODO: 在此參考您的程式所需的其他標頭。
#include <stdlib.h>
#include <cstddef>
#include <cstdint>

#include "quicklz.h"

#include "zstd.h"

#include "htslib/bgzf.h"

extern "C" {
	BLOCKCOMPRESSION_API char* GetVersion();
	BLOCKCOMPRESSION_API size_t QuickLzCompress(char* source, int sourceLen, char* destination, int destinationLen);
	BLOCKCOMPRESSION_API size_t QuickLzDecompress(char* source, char* destination, int destinationLen);
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