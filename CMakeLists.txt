cmake_minimum_required(VERSION 3.10)

enable_language(ASM)

project(hello)

set(TARGET_LDSCRIPT "${CMAKE_SOURCE_DIR}/stx7105.ld")

set(TARGET_SOURCES
    "lib/printf/printf.c"
    "src/main.c"
    "src/stx7105_exc.c"
    "src/stx7105_utils.c"
    "startup_stx7105.S"
)

set(TARGET_INCLUDES
    "include"
    "lib/printf"
)

set(TARGET_FLAGS_HARDWARE "-m4-300 -ml")

set(CMAKE_C_FLAGS_DEBUG          "-DDEBUG -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG        "-DDEBUG -g -O0")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_C_FLAGS_RELEASE          "-DNDEBUG -O2 -flto")
set(CMAKE_CXX_FLAGS_RELEASE        "-DNDEBUG -O2 -flto")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto")

set(CMAKE_C_FLAGS          "${TARGET_FLAGS_HARDWARE} -Wall -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS        "${TARGET_FLAGS_HARDWARE} -Wall -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS_HARDWARE} -Wall -lc -lm -nostartfiles -Wl,--print-memory-usage -Wl,--gc-sections")

add_compile_definitions(${TARGET_DEFS})
include_directories(${TARGET_INCLUDES})

add_executable(${CMAKE_PROJECT_NAME}.elf ${TARGET_SOURCES})
target_link_options(${CMAKE_PROJECT_NAME}.elf
    PRIVATE "-T${TARGET_LDSCRIPT}"
    PRIVATE "-Wl,-Map=${CMAKE_PROJECT_NAME}.map"
)