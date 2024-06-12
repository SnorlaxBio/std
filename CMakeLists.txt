cmake_minimum_required(VERSION 3.22)
project(SnorlaxSTD C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSNORLAX_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSNORLAX_DEBUG")

include_directories(src)

set(SNORLAX_STD_SOURCE      src/snorlax.c
                            src/snorlax/random.c
                            src/snorlax/collection.c
                            src/snorlax/bucket.c
                            src/snorlax/list/linked/double.c
                            src/snorlax/list/linked/double/node.c)
set(SNORLAX_STD_HEADER      src/snorlax.h
                            src/snorlax/random.h
                            src/snorlax/collection.h
                            src/snorlax/bucket.h
                            src/snorlax/list/linked/double.h)

add_library(snorlax-std ${SNORLAX_STD_SOURCE}
                        ${SNORLAX_STD_HEADER})

target_compile_options(snorlax-std PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

add_executable(snorlax-std-check src/main.c)
target_link_libraries(snorlax-std-check snorlax-std)
