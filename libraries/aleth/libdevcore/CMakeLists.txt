file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(devcore ${sources} ${headers})

target_link_libraries(devcore PUBLIC ${JSONCPP_LINK_LIBRARIES} ethash Boost::functional Boost::multiprecision Boost::exception Boost::log)
target_include_directories(devcore SYSTEM PUBLIC ${JSONCPP_INCLUDE_DIRS} ../)
