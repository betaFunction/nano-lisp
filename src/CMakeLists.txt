set(SOURCE_FILES
#        src/include/lexer.h
#        src/include/parser.h

	executable.cc
        nanolisp.cc
        lexer.cc
        parser.cc
#        src/include/checkers.hpp
#        src/checkers/checkers.cc

        interpreter.cc
#        src/include/interpreter.h
#        src/include/nanolisp.h
        )
set(REPL_SOURCE_FILES main.cc)



add_library(nanolisp-lib ${SOURCE_FILES})
#target_include_directories(nanolisp-lib INTERFACE src/include)


add_executable(nanolisp ${REPL_SOURCE_FILES})
target_include_directories(nanolisp
        PUBLIC src/include)
target_link_libraries(nanolisp nanolisp-lib)


