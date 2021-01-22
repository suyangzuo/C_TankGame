cmake_minimum_required(VERSION 3.0.0)
project(C_Game VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("C:/Program Files/mingw64/include")
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/mingw64/lib" 
"C:/Program Files/mingw64/x86_64-w64-mingw32/lib")

add_executable(C_Game main.c)

target_link_libraries(C_Game PRIVATE
    mingw32
    libSDL2.a
    libSDL2_image.a
    libSDL2main.a
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
