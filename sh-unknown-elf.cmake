set(CMAKE_C_COMPILER   sh-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER sh-unknown-elf-g++)

# Make CMake happy about those compilers
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Poor old Windows...
if(WIN32)
    set(CMAKE_SYSTEM_NAME "Generic")
endif()