#include "tokenizer.h"

using namespace std;

vector<string> ECPP::Tokenizer::tokenize(string &s)
{
    Tokenizer tokenizer;
    vector<string> ret;
    string token;

    for(auto it = s.begin(); it != s.end(); it++)
    {
        token = tokenizer.feed(*it);
        if (!token.empty())
        {
            ret.push_back(token);
            token = string();
        }
    }

    token = tokenizer.getToken();
    if (!token.empty())
        ret.push_back(token);

    return ret;
}

string ECPP::Tokenizer::feed_STRING_BUILD(char ch)
{
    if (ch == '<') {
        state = Tokenizer::HAVE_START_TAG;
        return "";
    }

    token.push_back(ch);

    return "";
}

string ECPP::Tokenizer::feed_HAVE_START_TAG(char ch)
{
    switch(ch)
    {
        case '%':
            state = Tokenizer::HAVE_START_PERCENT;
            return "";
        default:
            state = Tokenizer::STRING_BUILD;
            token.push_back('<');
            token.push_back(ch);
            return "";
    }
}

string ECPP::Tokenizer::feed_HAVE_START_PERCENT(char ch)
{
    string ret;

    switch(ch)
    {
        case '%':
            // <%%
            token.push_back('<');
            token.push_back('%');
            state = Tokenizer::STRING_BUILD;
            return "";
        case '"':
            ret = token;
            token = "<%\"";
            state = Tokenizer::IN_QUOTE;
            return ret;
         default:
            ret = token;
            token = "<%";
            token.push_back(ch);
            state = Tokenizer::IN_BLOCK;
            return ret;
    }
}

string ECPP::Tokenizer::feed_IN_BLOCK(char ch)
{
    switch(ch)
    {
        case '%':
            state = HAVE_PERCENT_IN_BLOCK;
            return "";
        case '"':
            token.push_back(ch);
            state = IN_QUOTE;
            return "";
        default:
            token.push_back(ch);
            return "";
    }
}

string ECPP::Tokenizer::feed_HAVE_PERCENT_IN_BLOCK(char ch)
{
    string ret;

    switch(ch)
    {
        case '>':
            ret = token + "%>";
            state = STRING_BUILD;
            token = "";
            return ret;
        case '%':
            token.push_back('%');
            state = STRING_BUILD;
            return "";
        default:
            token.push_back('%');
            token.push_back(ch);
            state = IN_BLOCK;
            return "";
    }
}

string ECPP::Tokenizer::feed_IN_QUOTE(char ch)
{
    switch(ch)
    {
        case '\\':
            state = BACKSLASH_IN_QUOTE;
            return "";
        case '"':
            token.push_back(ch);
            state = IN_BLOCK;
            return "";
        default:
            token.push_back(ch);
            return "";
    }

}
string ECPP::Tokenizer::feed_BACKSLASH_IN_QUOTE(char ch)
{
    switch(ch)
    {
        case '"':
            token.push_back('"');
            state = IN_QUOTE;
            return "";
        default:
            token.push_back('\\');
            token.push_back(ch);
            state = IN_QUOTE;
            return "";
    }
}


string ECPP::Tokenizer::feed(char ch)
{
    switch(state) {
        case STRING_BUILD: return feed_STRING_BUILD(ch);
        case HAVE_START_TAG: return feed_HAVE_START_TAG(ch);
        case HAVE_START_PERCENT: return feed_HAVE_START_PERCENT(ch);
        case IN_BLOCK: return feed_IN_BLOCK(ch);
        case BACKSLASH_IN_QUOTE: return feed_BACKSLASH_IN_QUOTE(ch);
        case HAVE_PERCENT_IN_BLOCK: return feed_HAVE_PERCENT_IN_BLOCK(ch);
        case IN_QUOTE: return feed_IN_QUOTE(ch);

        default: return "";
    }
}
