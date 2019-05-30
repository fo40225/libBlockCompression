# CMakeList.txt: 最上層的 CMake 專案檔，執行全域設定
# 並在這裡包含子專案。
#
cmake_minimum_required (VERSION 3.8)

project ("BlockCompression")

include(ExternalProject)
ExternalProject_Add(project_zstd
	GIT_REPOSITORY    https://github.com/facebook/zstd.git
	GIT_TAG           v1.4.0
	PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/external
	SOURCE_SUBDIR build/cmake
	CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(project_zstd INSTALL_DIR)
add_library(zstd STATIC IMPORTED)
set_target_properties(zstd PROPERTIES
	IMPORTED_LOCATION ${INSTALL_DIR}/lib/libzstd.a)
add_dependencies(zstd project_zstd)

ExternalProject_Add(project_htslib
	GIT_REPOSITORY    https://github.com/samtools/htslib.git
	GIT_TAG           1.9
	BUILD_IN_SOURCE 1
	PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/external
	CONFIGURE_COMMAND autoreconf && ./configure --prefix=<INSTALL_DIR>
	BUILD_COMMAND make
	INSTALL_COMMAND make install
)

add_library(htslib STATIC IMPORTED)
set_target_properties(htslib PROPERTIES
	IMPORTED_LOCATION ${INSTALL_DIR}/lib/libhts.a)
add_dependencies(htslib project_htslib)

include_directories(${INSTALL_DIR}/include)

# 包含子專案。
add_subdirectory ("BlockCompression")
