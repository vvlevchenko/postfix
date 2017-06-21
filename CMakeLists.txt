set(LLVM_LINK_COMPONENTS
        Support
        )

add_llvm_tool(postfix
        postfix.cpp
        Lexer.cpp
        )