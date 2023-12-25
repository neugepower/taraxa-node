file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(devcore ${sources} ${headers})

target_link_libraries(devcore PUBLIC jsoncpp_lib ethash Boost::functional Boost::multiprecision Boost::exception Boost::log)
target_include_directories(devcore SYSTEM PUBLIC ../)
