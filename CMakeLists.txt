
cmake_minimum_required(VERSION 3.0)
project(test)

# set the C++ standard to C++ 11
set(CMAKE_CXX_STANDARD 20)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# Check platforms
if (CMAKE_HOST_WIN32)

    set(third_party_lib_dir ${PROJECT_SOURCE_DIR}/third_party/lib/win)

    aux_source_directory(src SRC)
    aux_source_directory(util  UTILS)

    find_package(glfw3 CONFIG REQUIRED)
    find_package(glm CONFIG REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glew REQUIRED)
    find_package(Stb REQUIRED)
    find_package(Freetype REQUIRED)

    add_executable(${PROJECT_NAME} main.cpp ${SRC} ${UTILS})

    target_link_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PRIVATE ${third_party_lib_dir}
    )

    target_link_libraries(${PROJECT_NAME}
    # PRIVATE OpenGL
    # PRIVATE GL
    PRIVATE glfw
    PRIVATE glm::glm
    PRIVATE GLEW::GLEW
    PRIVATE Freetype::Freetype
    PRIVATE IrrKlang
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_directory              # which executes "cmake - E copy_if_different..."
            ${third_party_lib_dir}                              # <--this is in-file
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)                 # <--this is out-file path

elseif(CMAKE_HOST_UNIX)

    # 添加对gdb的支持
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


    set(third_party_lib_dir ${PROJECT_SOURCE_DIR}/third_party/lib/linux)

    aux_source_directory(src SRC)
    aux_source_directory(util UTILS)

    add_executable(${PROJECT_NAME} main.cpp ${SRC} ${UTILS})

    target_include_directories(${PROJECT_NAME}
    PRIVATE    "/usr/include"
    PRIVATE    "/usr/include/freetype2"
    PRIVATE    "/usr/include/stb"
    )

    target_link_directories(${PROJECT_NAME}
    PRIVATE     ${third_party_lib_dir}
    )

    target_link_libraries(${PROJECT_NAME}
    PRIVATE     GL
    PRIVATE     glfw
    PRIVATE     GLEW
    PRIVATE     freetype
    PRIVATE     IrrKlang
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_directory              # which executes "cmake - E copy_if_different..."
            ${third_party_lib_dir}                              # <--this is in-file
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)                 # <--this is out-file path

endif()
