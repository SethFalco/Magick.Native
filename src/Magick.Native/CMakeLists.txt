cmake_minimum_required (VERSION 2.8.8)

project(${LIBRARY_NAME})

set(OPENMP false BOOL)

add_definitions(-DMAGICK_NATIVE_${PLATFORM} -DMAGICKCORE_QUANTUM_DEPTH=${DEPTH} -DMAGICKCORE_HDRI_ENABLE=${HDRI_ENABLE})

include_directories(. /usr/local/include /usr/local/include/ImageMagick-7)

set(LIB_DIR /usr/local/lib/)
set(CMAKE_CXX_FLAGS "-Wall -O3")

file(GLOB_RECURSE ALL_FILES . *.c)

if (PLATFORM STREQUAL "WASM")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind --no-heap-copy --no-entry --embed-file ${PROJECT_SOURCE_DIR}/Resources/xml@/xml -s WASM=1 -s STRICT=1 -s ALLOW_MEMORY_GROWTH=1 -s EMULATE_FUNCTION_POINTER_CASTS=1 -s SINGLE_FILE=1 -s MODULARIZE=1 -s EXPORT_NAME=\"'MagickNative'\" -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"getValue\", \"setValue\", \"UTF8ToString\", \"lengthBytesUTF8\", \"stringToUTF8\"]'")
    set(LIBSOCKFS sockfs.js)
else()
    file(GLOB_RECURSE CMAKE_FILES **/CMakeFiles/*.c)
    list(REMOVE_ITEM ALL_FILES ${CMAKE_FILES})
    set(LIBFONTCONFIG ${LIB_DIR}/libfontconfig.a)
    set(LIBWEBP ${LIB_DIR}/libwebpmux.a ${LIB_DIR}/libwebpdemux.a)
    set(LIBOPENEXR ${LIB_DIR}/libIlmImf-2_5.a ${LIB_DIR}/libIlmThread-2_5.a ${LIB_DIR}/libIex-2_5.a ${LIB_DIR}/libHalf-2_5.a ${LIB_DIR}/libImath-2_5.a)
    set(LIBAOM ${LIB_DIR}/libaom.a)
    set(LIBGLIB ${LIB_DIR}/libgio-2.0.a ${LIB_DIR}/libgobject-2.0.a ${LIB_DIR}/libgmodule-2.0.a ${LIB_DIR}/libffi.a ${LIB_DIR}/libglib-2.0.a -lresolv)
    set(LIBLQR ${LIB_DIR}/liblqr-1.a)
    set(LIBCAIRO ${LIB_DIR}/libcairo.a ${LIB_DIR}/libpixman-1.a)
    set(LIBPANGO ${LIB_DIR}/libpangocairo-1.0.a ${LIB_DIR}/libpango-1.0.a ${LIB_DIR}/libpangoft2-1.0.a ${LIB_DIR}/libfribidi.a ${LIB_DIR}/libharfbuzz.a)
    set(LIBRSVG ${LIB_DIR}/librsvg-2.a ${LIB_DIR}/libgdk_pixbuf-2.0.a ${LIB_DIR}/libcroco-0.6.a)
endif()

if (PLATFORM STREQUAL "MACOS")
    set(LIBICONV iconv)
    set(LIBINTL ${LIB_DIR}/libintl.a)
    set(CMAKE_MACOSX_RPATH 1)
    set(STDCPLUSPLUS stdc++)
elseif (PLATFORM STREQUAL "WASM")
    list(APPEND ALL_FILES foo.cxx)
else()
    set(LIBJPEGXL ${LIB_DIR}/libjxl.a ${LIB_DIR}/libhwy.a)
    find_package(Threads REQUIRED)
    list(APPEND ALL_FILES foo.cxx)
    set(THREADLIB Threads::Threads)
    set(STDCPLUSPLUS -static-libstdc++ -static-libgcc)
    if (OPENMP)
        set(LIBOPENMP -fopenmp)
    endif()
endif()

if (PLATFORM STREQUAL "WASM")
    add_executable(${LIBRARY_NAME} ${ALL_FILES})
else()
    add_library(${LIBRARY_NAME} SHARED ${ALL_FILES})
endif()

target_link_libraries(
    ${LIBRARY_NAME}

    ${LIB_DIR}/libMagickWand-7.${QUANTUM_NAME}.a
    ${LIB_DIR}/libMagickCore-7.${QUANTUM_NAME}.a

    ${LIBOPENEXR}
    ${LIBICONV}
    ${LIBINTL}
    ${LIBLQR}
    ${LIBRSVG}
    ${LIBPANGO}
    ${LIBCAIRO}
    ${LIBGLIB}
    ${LIBFONTCONFIG}
    ${LIBJPEGXL}
    ${LIB_DIR}/libfreetype.a
    ${LIB_DIR}/libxml2.a
    ${LIB_DIR}/libpng.a
    ${LIB_DIR}/libturbojpeg.a
    ${LIB_DIR}/libtiff.a
    ${LIBWEBP}
    ${LIB_DIR}/libwebp.a
    ${LIB_DIR}/libopenjp2.a
    ${LIB_DIR}/liblcms2.a
    ${LIB_DIR}/libheif.a
    ${LIBAOM}
    ${LIB_DIR}/libde265.a
    ${LIB_DIR}/libraw_r.a
    ${LIB_DIR}/libz.a

    ${LIBSOCKFS}
    ${LIBOPENMP}
    ${THREADLIB}
    ${STDCPLUSPLUS}
)