file(GLOB_RECURSE SRCS *.cpp)                                                                                                                                                                                   

include_directories(${CMAKE_SOURCE_DIR})

add_executable(weather_ot_user  ${SRCS})
                                             
target_link_libraries(weather_ot_user libOTe cryptoTools)