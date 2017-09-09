set(TARGET_NAME dep-graph)
set(SRC 
    Node.cpp
    DependencyGraph.cpp
    Visitor.cpp
    IndGroupsVisitor.cpp
    GraphIO.cpp
    GraphSVG.cpp
    )

add_executable(${TARGET_NAME} main.cpp ${SRC})
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
