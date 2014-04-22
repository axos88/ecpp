#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace ECPP {

    class Tokenizer {
        enum State { STRING_BUILD, HAVE_START_TAG, HAVE_START_PERCENT, IN_BLOCK, IN_QUOTE, BACKSLASH_IN_QUOTE, HAVE_PERCENT_IN_BLOCK};

    private:
        State state;
        string token;

        string feed_STRING_BUILD(char ch);
        string feed_HAVE_START_TAG(char ch);
        string feed_HAVE_START_PERCENT(char ch);
        string feed_IN_BLOCK(char ch);
        string feed_IN_QUOTE(char ch);
        string feed_BACKSLASH_IN_QUOTE(char ch);
        string feed_HAVE_PERCENT_IN_BLOCK(char ch);

        string getToken() { return token; }

        Tokenizer() : state(STRING_BUILD) {}
    public:

        string feed(char ch);
        static vector<string> tokenize(string &eccp);

    };

    class Lexer {

        public:
            class InvalidTokenError { };

            class Instruction
            {
                public:
                    enum InstructionType {
                        STRING_INSTRUCTION,
                        CODE_INSTRUCTION,
                        PRINT_INSTRUCTION,
                        INCLUDE_INSTRUCTION
                    };

                private:
                    InstructionType type;
                    string contents;

                public:
                    Instruction(InstructionType type, string token, string beginTag = "", string endTag = "") : type(type)
                    {
                        if (token.find(beginTag) != 0) throw InvalidTokenError();
                        if (token.rfind(endTag) != token.length() - endTag.length()) throw InvalidTokenError();

                        contents = token.substr(beginTag.length(), token.length() - beginTag.length() - endTag.length());
                    }

                    string Contents() { return contents; }
                    InstructionType Type() { return type; }
            };

            class StringInstruction : public Instruction {
                public:
                    StringInstruction(string contents) : Instruction(Instruction::STRING_INSTRUCTION, contents, "", "") { }
            };

            class CodeInstruction : public Instruction {
                public:
                    CodeInstruction(string contents) : Instruction(Instruction::CODE_INSTRUCTION, contents, "<% ", "%>") { }
            };

            class PrintInstruction : public Instruction {
                public:
                    PrintInstruction(string contents) : Instruction(Instruction::PRINT_INSTRUCTION, contents, "<%=", "%>") { }

            };

            class IncludeInstruction : public Instruction {
                public:
                    IncludeInstruction(string contents) : Instruction(Instruction::INCLUDE_INSTRUCTION, contents, "<%i", "%>") { }
            };


            vector<Instruction*> analyze(vector<string> tokens);
    };
}