# CMakeList.txt: BlockCompression 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

# 將來源新增到此專案的可執行檔。
add_library(BlockCompression SHARED "BlockCompression.cpp")

target_link_libraries(BlockCompression -Wl,--whole-archive quicklz -Wl,--no-whole-archive)
target_link_libraries(BlockCompression -Wl,--whole-archive zstd -Wl,--no-whole-archive)
target_link_libraries(BlockCompression -Wl,--whole-archive htslib -Wl,--no-whole-archive)

IF(MINGW)
	 target_link_libraries(BlockCompression ws2_32)
ENDIF()

find_package(ZLIB)
IF(ZLIB_FOUND)
	 target_link_libraries(BlockCompression ${ZLIB_LIBRARIES})
ENDIF()

find_package(BZip2)
IF(BZIP2_FOUND)
	 target_link_libraries(BlockCompression ${BZIP2_LIBRARIES})
ENDIF()

find_package(LibLZMA)
IF(LIBLZMA_FOUND)
	 target_link_libraries(BlockCompression ${LIBLZMA_LIBRARIES})
ENDIF()

#if(MSVC)
#    SET_TARGET_PROPERTIES(BlockCompression PROPERTIES LINK_FLAGS /DEF:${CMAKE_CURRENT_SOURCE_DIR}/deffile.def)
#endif()

IF(MINGW)
	SET_TARGET_PROPERTIES(BlockCompression PROPERTIES LINK_FLAGS ${CMAKE_CURRENT_SOURCE_DIR}/deffile.def)
endif()

# TODO: 新增測試，並視需要安裝目標。
