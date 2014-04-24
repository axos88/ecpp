#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <string>
#include <map>
#include <iostream>

#include "lexer.h"

using namespace std;

namespace ECPP {

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


        public:
            template<class T>void export_by_copy(string key, T& value)
            {
                set(key, typeid(T).name(), new T(value));
            };

            template<class T>void export_by_move(string key, T* value)
            {
                set(key, typeid(T).name(), (void*)value);
            }

            template<class T>T* import_ptr(string key)
            {
                return (T*)get(key, typeid(T).name());
            }

            template<class T>T import(string key)
            {
                return *import_ptr<T>(key);
            }
    };

};

#endif