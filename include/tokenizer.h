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
}