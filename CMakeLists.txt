cmake_minimum_required(VERSION 3.10)

enable_language(ASM)

project(benchmark)

set(TARGET_LDSCRIPT "${CMAKE_SOURCE_DIR}/stx7105.ld")

set(TARGET_SOURCES
    "lib/coremark/core_list_join.c"
    "lib/coremark/core_main.c"
    "lib/coremark/core_matrix.c"
    "lib/coremark/core_state.c"
    "lib/coremark/core_util.c"
    "lib/printf/printf.c"
    "src/core_portme.c"
    "src/stx7105_exc.c"
    "src/stx7105_utils.c"
    "src/syscalls.c"
    "startup_stx7105.S"
)

set(TARGET_INCLUDES
    "include"
    "lib/coremark"
    "lib/printf"
)

set(TARGET_DEFS
    "ITERATIONS=20000UL"
    "VALIDATION_RUN=1"
)

set(TARGET_FLAGS_HARDWARE "-m4-300 -ml")

set(TARGET_FLAGS_OPTS "-O3 -fomit-frame-pointer -funroll-all-loops -finline-limit=1000 -ftree-dominator-opts -fno-if-conversion2 -fselective-scheduling -fno-code-hoisting -freorder-blocks-and-partition")

set(CMAKE_C_FLAGS_DEBUG          "-DDEBUG -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG        "-DDEBUG -g -O0")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_C_FLAGS_RELEASE          "-DNDEBUG ${TARGET_FLAGS_OPTS}")
set(CMAKE_CXX_FLAGS_RELEASE        "-DNDEBUG ${TARGET_FLAGS_OPTS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "    ")

set(CMAKE_C_FLAGS          "${TARGET_FLAGS_HARDWARE} -Wall -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS        "${TARGET_FLAGS_HARDWARE} -Wall -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS_HARDWARE} -specs=nosys.specs -Wall -lc -lm -nostartfiles -Wl,--print-memory-usage -Wl,--gc-sections")

add_compile_definitions(${TARGET_DEFS})
include_directories(${TARGET_INCLUDES})

add_executable(${CMAKE_PROJECT_NAME}.elf ${TARGET_SOURCES})
target_link_options(${CMAKE_PROJECT_NAME}.elf
    PRIVATE "-T${TARGET_LDSCRIPT}"
    PRIVATE "-Wl,-Map=${CMAKE_PROJECT_NAME}.map"
)