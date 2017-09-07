cmake_minimum_required(VERSION 2.8)

set (PROY palindrome_bot)
project (${PROY} C CXX)

set(Boost_USE_MULTITHREADED ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system iostreams REQUIRED)

# Source files folder
set (SRC_DIR src)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Bot source files
set (SOURCE
    ${SRC_DIR}/main.cpp
)

include_directories(/usr/local/include
    ${OPENSSL_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add executable
add_executable (${PROY} ${SOURCE})

target_link_libraries(${PROY}
    /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES}
)

