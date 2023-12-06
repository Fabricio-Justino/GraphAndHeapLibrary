set(SOURCES
    ./main.cpp
)

add_executable(GraphAlgorithm ${SOURCES})

target_link_libraries(GraphAlgorithm PRIVATE GraphLibrary)