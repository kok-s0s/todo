# CMakeList.txt: todo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("todo")

include_directories (
  ${CMAKE_SOURCE_DIR}/src/external/sqlite
)

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/external/sqlite/sqlite3.c
	"src/main.cpp"
	"src/model/item.cpp"
	"src/model/list.cpp"
	"src/view/view.cpp"
	"src/controller/controller.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET todo PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
