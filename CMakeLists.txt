# CMakeList.txt: 最上層的 CMake 專案檔，執行全域設定
# 並在這裡包含子專案。
#
cmake_minimum_required (VERSION 3.8)

project ("BlockCompression")

include(ExternalProject)

ExternalProject_Add(project_zstd
	GIT_REPOSITORY    https://github.com/facebook/zstd.git
	GIT_TAG           v1.4.0
	PREFIX ${PROJECT_BINARY_DIR}/external
	#PREFIX ${CMAKE_SOURCE_DIR}/external
	UPDATE_COMMAND git cherry-pick f837326f1130a0e521bc5e39b94936816fff9486
	SOURCE_SUBDIR build/cmake
	CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	BUILD_COMMAND cmake --build . -- -j $(nproc)
)

ExternalProject_Get_Property(project_zstd INSTALL_DIR)
file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
add_library(zstd STATIC IMPORTED)
set_target_properties(zstd PROPERTIES
  IMPORTED_LOCATION ${INSTALL_DIR}/lib/libzstd.a
#	IMPORTED_LOCATION ${INSTALL_DIR}/lib/zstd_static.lib
	 INTERFACE_INCLUDE_DIRECTORIES  ${INSTALL_DIR}/include
	)
add_dependencies(zstd project_zstd)

SET(VAR "-fpic -O3 -DNDEBUG")
ExternalProject_Add(project_htslib
	GIT_REPOSITORY    https://github.com/samtools/htslib.git
	GIT_TAG           1.9
	BUILD_IN_SOURCE 1
	PREFIX ${PROJECT_BINARY_DIR}/external
	CONFIGURE_COMMAND autoreconf && ./configure --prefix=<INSTALL_DIR>
	BUILD_COMMAND make CFLAGS=${VAR} -j $(nproc)
	INSTALL_COMMAND make install
)

ExternalProject_Get_Property(project_htslib INSTALL_DIR)
file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
add_library(htslib STATIC IMPORTED)
set_target_properties(htslib PROPERTIES
	IMPORTED_LOCATION ${INSTALL_DIR}/lib/libhts.a
	 INTERFACE_INCLUDE_DIRECTORIES  ${INSTALL_DIR}/include
	)
add_dependencies(htslib project_htslib)

# 包含子專案。
add_subdirectory ("QuickLZ")
add_subdirectory ("BlockCompression")
