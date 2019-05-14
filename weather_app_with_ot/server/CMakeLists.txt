file(GLOB_RECURSE SRCS *.cpp)                                                                                                                                                                                   

include_directories(${CMAKE_SOURCE_DIR})

add_executable(weather_ot_server  ${SRCS})
                                             
target_link_libraries(weather_ot_server libOTe cryptoTools)