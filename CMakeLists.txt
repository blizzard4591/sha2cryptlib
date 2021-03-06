cmake_minimum_required (VERSION 2.8.11)

# Set project name
project (sha2CryptLib CXX C)

# Import the GENERATE_EXPORT_HEADER macros
include(GenerateExportHeader)
# Import the CHECK_INCLUDE_FILES macros
include(CheckIncludeFiles)
# Import the check_prototype_definition macros
include(CheckPrototypeDefinition)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add base folder for better inclusion paths
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

# Let the user decide whether he wants SHARED or STATIC libs
option(SHA2CRYPTLIB_OPTION_BUILD_SHARED_LIBS "Sets whether to build SHARED (on) or STATIC (off) libraries." ON)


# Main Sources
file(GLOB_RECURSE SHA2CRYPTLIB_GENERAL_HEADERS ${PROJECT_SOURCE_DIR}/src/general/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_GENERAL_SOURCES ${PROJECT_SOURCE_DIR}/src/general/*.c)

file(GLOB_RECURSE SHA2CRYPTLIB_INTERFACEC_HEADERS ${PROJECT_SOURCE_DIR}/src/interface-c/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_INTERFACEC_SOURCES ${PROJECT_SOURCE_DIR}/src/interface-c/*.c)

file(GLOB_RECURSE SHA2CRYPTLIB_INTERFACECPP_HEADERS ${PROJECT_SOURCE_DIR}/src/interface-cpp/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_INTERFACECPP_SOURCES ${PROJECT_SOURCE_DIR}/src/interface-cpp/*.cpp)

file(GLOB_RECURSE SHA2CRYPTLIB_TESTSHA256_HEADERS ${PROJECT_SOURCE_DIR}/src/test-sha256/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_TESTSHA256_SOURCES ${PROJECT_SOURCE_DIR}/src/test-sha256/*.c)

file(GLOB_RECURSE SHA2CRYPTLIB_TESTSHA512_HEADERS ${PROJECT_SOURCE_DIR}/src/test-sha512/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_TESTSHA512_SOURCES ${PROJECT_SOURCE_DIR}/src/test-sha512/*.c)

file(GLOB_RECURSE SHA2CRYPTLIB_SIMPLEUTILITY_HEADERS ${PROJECT_SOURCE_DIR}/src/simple-utility/*.h)
file(GLOB_RECURSE SHA2CRYPTLIB_SIMPLEUTILITY_SOURCES ${PROJECT_SOURCE_DIR}/src/simple-utility/*.cpp)

#############################################################
##
##	CMake-generated Config File for sha2CryptLib
##
#############################################################

if (CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -pedantic")
	add_definitions("/D_GNU_SOURCE") # to enable mempcpy in string.h
elseif(MSVC)
	#
else(CLANG)
	# Set up some Xcode specific settings
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	add_definitions("/D_GNU_SOURCE") # to enable mempcpy in string.h
endif()

# Test for type alignment
try_run(SHA2CRYPTLIB_RUN_RESULT_TYPEALIGNMENT SHA2CRYPTLIB_COMPILE_RESULT_TYPEALIGNMENT
	${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/CMakeAlignmentCheck.cpp"
	COMPILE_OUTPUT_VARIABLE OUTPUT_TEST_VAR
	RUN_OUTPUT_VARIABLE RUN_OUTPUT_VAR
)
if(NOT SHA2CRYPTLIB_COMPILE_RESULT_TYPEALIGNMENT)
	message(FATAL_ERROR "Could not test type alignment, there was an Error while compiling the file ${PROJECT_SOURCE_DIR}/CMakeAlignmentCheck.cpp: ${OUTPUT_TEST_VAR}")
elseif(SHA2CRYPTLIB_RUN_RESULT_TYPEALIGNMENT EQUAL 0)
	string(REGEX REPLACE "^Alignment of type uint32_t: ([0-9]+)[^0-9A-Za-z]*Alignment of type uint64_t: [0-9]+[^0-9A-Za-z]*$" "\\1" SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT32 "${RUN_OUTPUT_VAR}")
	string(REGEX REPLACE "^Alignment of type uint32_t: [0-9]+[^0-9A-Za-z]*Alignment of type uint64_t: ([0-9]+)[^0-9A-Za-z]*$" "\\1" SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT64 "${RUN_OUTPUT_VAR}")
	message(STATUS "Result of Type Alignment Check: OK (uint32_t: ${SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT32}, uint64_t: ${SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT64}).")
else()
	message(FATAL_ERROR "Result of Type Alignment Check: FAILED (Code ${SHA2CRYPTLIB_RUN_RESULT_TYPEALIGNMENT})")
endif()

# Test for sys/param.h, endian.h, etc.
CHECK_INCLUDE_FILES("sys/param.h" SHA2CRYPTLIB_CONFIG_HAVE_SYSPARAM_H)
if (SHA2CRYPTLIB_CONFIG_HAVE_SYSPARAM_H)
	set(SHA2CRYPTLIB_CONFIG_HAVE_SYSPARAM_H_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_SYSPARAM_H_DEF "undef")
endif()

CHECK_INCLUDE_FILES("endian.h" SHA2CRYPTLIB_CONFIG_HAVE_ENDIAN_H)
if (SHA2CRYPTLIB_CONFIG_HAVE_ENDIAN_H)
	set(SHA2CRYPTLIB_CONFIG_HAVE_ENDIAN_H_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_ENDIAN_H_DEF "undef")
endif()

CHECK_INCLUDE_FILES("alloca.h" SHA2CRYPTLIB_CONFIG_HAVE_ALLOCA_H)
if (SHA2CRYPTLIB_CONFIG_HAVE_ALLOCA_H)
	set(SHA2CRYPTLIB_CONFIG_HAVE_ALLOCA_H_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_ALLOCA_H_DEF "undef")
endif()

try_compile(SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY ${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/CMakeCheckFunctionMempcpy.c" OUTPUT_VARIABLE SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY_OUPUT)
if (SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY)
	set(SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY_DEF "undef")
endif()

try_compile(SHA2CRYPTLIB_CONFIG_HAVE_MEMCPY ${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/CMakeCheckFunctionMemcpy.c" OUTPUT_VARIABLE SHA2CRYPTLIB_CONFIG_HAVE_MEMCPY_OUPUT)
if (SHA2CRYPTLIB_CONFIG_HAVE_MEMCPY)
	set(SHA2CRYPTLIB_CONFIG_HAVE_MEMCPY_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_MEMCPY_DEF "undef")
endif()

try_compile(SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY ${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/CMakeCheckFunctionStpncpy.c" OUTPUT_VARIABLE SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY_OUPUT)
if (SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY)
	set(SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY_DEF "define")
else()
	set(SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY_DEF "undef")
endif()

# Configure a header file to pass some of the CMake settings to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/sha2cryptLibConfig.h.in"
	"${PROJECT_BINARY_DIR}/sha2cryptLibConfig.h"
)

if (SHA2CRYPTLIB_OPTION_BUILD_SHARED_LIBS)
	set(SHA2CRYPTLIB_OPTION_LIBTYPE SHARED)
else()
	set(SHA2CRYPTLIB_OPTION_LIBTYPE STATIC)
endif()

# Add the executables and libraries
add_library(sha2CryptLibC ${SHA2CRYPTLIB_OPTION_LIBTYPE} ${SHA2CRYPTLIB_GENERAL_HEADERS} ${SHA2CRYPTLIB_GENERAL_SOURCES} ${SHA2CRYPTLIB_INTERFACEC_HEADERS} ${SHA2CRYPTLIB_INTERFACEC_SOURCES})
add_library(sha2CryptLibCpp ${SHA2CRYPTLIB_OPTION_LIBTYPE} ${SHA2CRYPTLIB_GENERAL_HEADERS} ${SHA2CRYPTLIB_GENERAL_SOURCES} ${SHA2CRYPTLIB_INTERFACECPP_HEADERS} ${SHA2CRYPTLIB_INTERFACECPP_SOURCES})
set_target_properties(sha2CryptLibC PROPERTIES PUBLIC_HEADER "${PROJECT_BINARY_DIR}/sha2CryptLibC_Export.h;src/general/sha256crypt.h;src/general/sha512crypt.h")
set_target_properties(sha2CryptLibCpp PROPERTIES PUBLIC_HEADER "${PROJECT_BINARY_DIR}/sha2CryptLibCpp_Export.h;src/general/sha256crypt.h;src/general/sha512crypt.h")

add_executable(sha2CryptLibTestSha256 ${SHA2CRYPTLIB_INTERFACEC_HEADERS} ${SHA2CRYPTLIB_INTERFACEC_SOURCES} ${SHA2CRYPTLIB_TESTSHA256_HEADERS} ${SHA2CRYPTLIB_TESTSHA256_SOURCES})
add_executable(sha2CryptLibTestSha512 ${SHA2CRYPTLIB_INTERFACEC_HEADERS} ${SHA2CRYPTLIB_INTERFACEC_SOURCES} ${SHA2CRYPTLIB_TESTSHA512_HEADERS} ${SHA2CRYPTLIB_TESTSHA512_SOURCES})

target_link_libraries(sha2CryptLibTestSha256 sha2CryptLibC)
target_link_libraries(sha2CryptLibTestSha512 sha2CryptLibC)

add_executable(sha2CryptLibSimpleUtility ${SHA2CRYPTLIB_SIMPLEUTILITY_HEADERS} ${SHA2CRYPTLIB_SIMPLEUTILITY_SOURCES})
target_link_libraries(sha2CryptLibSimpleUtility sha2CryptLibCpp)

GENERATE_EXPORT_HEADER(sha2CryptLibC BASE_NAME sha2CryptLibC EXPORT_MACRO_NAME sha2CryptLibC_EXPORT EXPORT_FILE_NAME sha2CryptLibC_Export.h)
GENERATE_EXPORT_HEADER(sha2CryptLibCpp BASE_NAME sha2CryptLibCpp EXPORT_MACRO_NAME sha2CryptLibCpp_EXPORT EXPORT_FILE_NAME sha2CryptLibCpp_Export.h STATIC_DEFINE sha2CryptLibCpp_BUILT_AS_STATIC)

install(TARGETS sha2CryptLibTestSha256 sha2CryptLibTestSha512 sha2CryptLibSimpleUtility sha2CryptLibC sha2CryptLibCpp
		EXPORT sha2CryptLib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
		INCLUDES DESTINATION include
		PUBLIC_HEADER DESTINATION include
		)
install(EXPORT sha2CryptLib NAMESPACE sha2CryptLib_ DESTINATION lib/sha2CryptLib)
		