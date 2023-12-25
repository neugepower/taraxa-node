file(GLOB sources "*.cpp" "*.h")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LZ4 REQUIRED liblz4)
add_library(p2p ${sources})
target_link_libraries(p2p PUBLIC devcrypto ${LZ4_LINK_LIBRARIES} Boost::asio Boost::system)

target_include_directories(p2p SYSTEM PUBLIC ../)

if(MINIUPNPC)
    target_link_libraries(p2p PUBLIC "${MINIUPNPC_LIBRARY}")
    target_include_directories(p2p SYSTEM PUBLIC "${MINIUPNPC_INCLUDE_DIR}")
    target_compile_definitions(p2p PUBLIC ETH_MINIUPNPC)
endif()
