set(HEADERS
    include/metrics/metrics_service.hpp
)

set(SOURCES
    src/metrics_service.cpp
)

add_library(metrics ${SOURCES} ${HEADERS})
target_include_directories(metrics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(metrics PUBLIC metrics-rust)


install(TARGETS metrics
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
