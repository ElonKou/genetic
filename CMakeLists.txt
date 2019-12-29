project(biulab)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

aux_source_directory(./base BIULAB_SRC)
aux_source_directory(./src BIULAB_SRC)
aux_source_directory(./lib/frame BIULAB_SRC)
aux_source_directory(./lib/imgui BIULAB_SRC)
aux_source_directory(./lib/tools BIULAB_SRC)

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/lib/imgui
)

# [config]
set(BIULAB_INSTALL_PATH ${PROJECT_SOURCE_DIR}/install)
configure_file(
    "${PROJECT_SOURCE_DIR}/BiuLabConfig.hh.in"
    "${PROJECT_SOURCE_DIR}/include/BiuLabConfig.hh"
)

# [build]
add_executable(biulab ${BIULAB_SRC})

target_link_libraries(biulab glfw dl GLEW GL)

# [install]
set(CMAKE_INSTALL_PREFIX ${BIULAB_INSTALL_PATH})

install(TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib
)

install(DIRECTORY resources DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY include/ lib/imgui/ 
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
)