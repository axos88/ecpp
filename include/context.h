#include <string>
#include <map>
#include <iostream>

#include "lexer.h"

using namespace std;

namespace ECPP {

    #define ECPP_EXPORT(context, key, type, value) \
        context.set(key, #type, (void*)&value)

    #define ECPP_EXPORT_PTR(context, key, type, value) \
        context.set(key, #type, (void*)value)

    #define ECPP_IMPORT_PTR(context, key, type, varname) \
        type* varname = (type*)context.get(key, #type);

    #define ECPP_IMPORT(context, key, type, varname) \
        type varname = *(type*)context.get(key, #type);

    class RenderContext {

        public:
            class InvalidTypeError {};
            class KeyNotFoundError {};

            struct Entry {
                string type;
                void* ptr;

                Entry(string type, void* ptr) : type(type), ptr(ptr) { }
                Entry() : type(""), ptr(0) {}
            };

        private:
            map<string, Entry> entries;

        public:
            void* get(string name, string type)
            {
                auto it = entries.find(name);

                if (it == entries.end())
                    throw KeyNotFoundError();

                Entry e = it->second;

                if (e.type != type) throw InvalidTypeError();

                return e.ptr;
            }
            void set(string name, string type, void* value) {
                entries[name] = Entry(type, value);
            }
    };

};