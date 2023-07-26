cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(todo)

include_directories(
	${CMAKE_SOURCE_DIR}/external/sqlite
	${CMAKE_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/external/sqlite/sqlite3.c
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/model/todo_item.cpp
	${CMAKE_SOURCE_DIR}/src/model/todo_list.cpp
	${CMAKE_SOURCE_DIR}/src/view/todo_view.cpp
	${CMAKE_SOURCE_DIR}/src/controller/todo_controller.cpp
)

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET todo PROPERTY CXX_STANDARD 20)
endif()
