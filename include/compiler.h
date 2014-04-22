#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "lexer.h"

using namespace std;

namespace ECPP {

    class Compiler {

        class UnknownInstructionType {};

        private:
            string renderString(Lexer::Instruction &i);
            string renderCode(Lexer::Instruction &i);
            string renderInclude(Lexer::Instruction &i);
            string renderPrint(Lexer::Instruction &i);
        public:
            map<string, string> render(vector<Lexer::Instruction> &input);
    };

};

#endif