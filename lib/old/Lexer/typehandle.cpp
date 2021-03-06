#include <string>
#include "../tokens.h"
#include "./LFA.hpp"


void ObjectsHandle(LexerFunctionArg& lfa)
{
    std::string name = lfa.current_token->literal_token;

    if (name == ("struct" || "class") )
        object_type_handle(lfa);
}

void object_type_handle(LexerFunctionArg& lfa)
{
    // typedefing anonymous struct not currently
    // supported. I'll do that later
    UserTypes ut(*(lfa.current_token++));
    ut.end_of_scope = find_end_of_struct(lfa);
    
}

Tokens::Token find_end_of_struct(LexerFunctionArg& lfa)
{
    int stack = 0;
    
    for (auto i : tv) {
        for (auto token : i) {
            std::string lt = token.literal_token;
            if (lt == "{")
                stack++;
            if (lt == "}")
                stack--;

            if (stack == 0) {
                return token;
            }
        }
    }
}