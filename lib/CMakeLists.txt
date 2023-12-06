
project(GraphLibrary)

file(GLOB HEAP ./heap/*)
file(GLOB GRAPH ./graph/*)
file(GLOB ALG ./algorithm/*)

add_library(GraphLibrary INTERFACE
        ${ALG}
        ${HEAP}
        ${GRAPH})

set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/graph
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithm
        ${CMAKE_CURRENT_SOURCE_DIR}/heap
)

target_include_directories(GraphLibrary INTERFACE ${INCLUDES})
