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
                            src/snorlax/queue.c
                            src/snorlax/memory.c
                            src/snorlax/collection.c
                            src/snorlax/buffer.c
                            src/snorlax/thread/posix.c
                            src/snorlax/sync/posix/mutex.c
                            src/snorlax/queue/node.c
                            src/snorlax/list/linked/double.c
                            src/snorlax/list/linked/double/node.c
                            src/snorlax/buffer/pool.c
                            src/snorlax/buffer/mem.c
                            src/snorlax/string/simple/deserializer.c
                            src/snorlax/string/simple/serializer.c
                            src/snorlax/deserializer.c
                            src/snorlax/serializer.c
                            src/snorlax/nanosecond.c)

set(SNORLAX_STD_HEADER      src/snorlax.h
                            src/snorlax/thread.h
                            src/snorlax/random.h
                            src/snorlax/queue.h
                            src/snorlax/list.h
                            src/snorlax/collection.h
                            src/snorlax/buffer.h
                            src/snorlax/thread/posix.h
                            src/snorlax/sync/posix/mutex.h
                            src/snorlax/buffer/pool.h
                            src/snorlax/buffer/mem.h
                            src/snorlax/string/simple/deserializer.h
                            src/snorlax/string/simple/serializer.h
                            src/snorlax/deserializer.h
                            src/snorlax/serializer.h
                            src/snorlax/nanosecond.h)

add_library(snorlax-std ${SNORLAX_STD_SOURCE}
                        ${SNORLAX_STD_HEADER})

target_compile_options(snorlax-std PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-std-check src/main.c)
target_link_libraries(snorlax-std-check snorlax-std)

install(TARGETS snorlax-std ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
                  FILES_MATCHING PATTERN "*.h")
