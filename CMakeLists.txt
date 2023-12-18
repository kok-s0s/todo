cmake_minimum_required(VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(todo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
	${CMAKE_SOURCE_DIR}/external/sqlite
	${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(external/FTXUI)

add_executable(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/external/sqlite/sqlite3.c
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/todo_item.cpp
	${CMAKE_SOURCE_DIR}/src/todo_list.cpp
	${CMAKE_SOURCE_DIR}/src/todo_tui.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

