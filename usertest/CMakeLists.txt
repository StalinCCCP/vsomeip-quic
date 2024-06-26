cmake_minimum_required (VERSION 3.13)

set (CMAKE_CXX_FLAGS "-g -std=c++20")

find_package (vsomeip3 3.4.10 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service-example service-example.cpp)
target_link_libraries(service-example vsomeip3 ${Boost_LIBRARIES})

add_executable(client-example client-example.cpp)
target_link_libraries(client-example vsomeip3 ${Boost_LIBRARIES})

add_executable(quic-client-example quic-client-example.cpp)
target_link_libraries(quic-client-example vsomeip3 ${Boost_LIBRARIES})

add_subdirectory(json)
add_executable(client-presentation client-presentation.cpp)
target_link_libraries(client-presentation vsomeip3 ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)