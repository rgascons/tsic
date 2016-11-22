add_subdirectory(AST)
add_subdirectory(Lex)
add_subdirectory(Parser)
add_subdirectory(Utils)
add_subdirectory(tsic)

add_executable(tsic main.cpp)

target_link_libraries(tsic
	taiseiLex
	taiseiParser
	taiseiUtils
	tsicLib
	taiseiAST
	)

target_link_libraries(tsic ${llvm_libs})
