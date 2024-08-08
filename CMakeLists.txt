cmake_minimum_required(VERSION 3.22)
project(SnorlaxSTD C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSNORLAX_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

include_directories(src)

set(SNORLAX_STD_SOURCE      src/snorlax.c
                            src/snorlax/thread.c
                            src/snorlax/sync.c
                            src/snorlax/random.c
                            src/snorlax/memory.c
                            src/snorlax/collection.c
                            src/snorlax/buffer.c
                            src/snorlax/thread/posix.c
                            src/snorlax/sync/posix/mutex.c
                            src/snorlax/buffer/mem.c
                            src/snorlax/buffer/mem/node.c
                            src/snorlax/buffer/list.c
                            src/snorlax/buffer/list/node.c
                            src/snorlax/nanosecond.c
                            src/snorlax/hashtable.c
                            src/snorlax/hashtable/bucket.c
                            src/snorlax/hashtable/list.c
                            src/snorlax/hashtable/node.c)

set(SNORLAX_STD_HEADER      src/snorlax.h
                            src/snorlax/thread.h
                            src/snorlax/random.h
                            src/snorlax/list.h
                            src/snorlax/collection.h
                            src/snorlax/buffer.h
                            src/snorlax/thread/posix.h
                            src/snorlax/sync/posix/mutex.h
                            src/snorlax/buffer/mem.h
                            src/snorlax/buffer/list.h
                            src/snorlax/nanosecond.h
                            src/snorlax/hashtable.h)

add_library(snorlax-std ${SNORLAX_STD_SOURCE}
                        ${SNORLAX_STD_HEADER})

target_compile_options(snorlax-std PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-std-check src/main.c)
target_link_libraries(snorlax-std-check snorlax-std)

add_executable(snorlax-std-mem-benchmark src/snorlax/memory/benchmark.c)

install(TARGETS snorlax-std ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
                  FILES_MATCHING PATTERN "*.h")
