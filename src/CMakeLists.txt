set(TARGET_NAME dep-graph)
set(SRC Node.cpp DependencyGraph.cpp GraphIO.cpp)

add_executable(${TARGET_NAME} main.cpp ${SRC})
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
