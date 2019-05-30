# CMakeList.txt: BlockCompression 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

IF(MSVC)
	add_compile_definitions(BLOCKCOMPRESSION_EXPORTS)
ENDIF()

# 將來源新增到此專案的可執行檔。

file(GLOB BLOCKCOMPRESSION_SRC
	"*.cpp"
	"*.h"
	"*.c"
)

add_library(BlockCompression SHARED ${BLOCKCOMPRESSION_SRC})
target_link_libraries(BlockCompression zstd)
target_link_libraries(BlockCompression htslib)

# TODO: 新增測試，並視需要安裝目標。
