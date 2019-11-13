#include <iostream>
#include "char_check.hpp"
using namespace std;

bool isNotLetter(char c)    // excluding hyphens
{
    if (c == '0')       return true;
    else if (c == '1')  return true;
    else if (c == '2')  return true;
    else if (c == '3')  return true;
    else if (c == '4')  return true;
    else if (c == '5')  return true;
    else if (c == '6')  return true;
    else if (c == '7')  return true;
    else if (c == '8')  return true;
    else if (c == '9')  return true;
    else if (c == '\"') return true;
    else if (c == ',')  return true;
    else if (c == '.')  return true;
    else if (c == '?')  return true;
    else if (c == ';')  return true;
    else if (c == ':')  return true;
    else if (c == '\'') return true;
    else if (c == '!')  return true;
    else if (c == '(')  return true;
    else if (c == ')')  return true;
    else if (c == '[')  return true;
    else if (c == ']')  return true;
    else if (c == '$')  return true;
    else if (c == '/')  return true;
    else if (c == '&')  return true;
    else if (c == '^')  return true;
    else if (c == '*')  return true;
    else if (c == '#')  return true;
    else if (c == '@')  return true;
    else if (c == '~')  return true;
    else if (c == '`')  return true;
    else if (c == '_')  return true;
    else if (c == '+')  return true;
    else if (c == '=')  return true;
    else if (c == '{')  return true;
    else if (c == '}')  return true;
    else if (c == '\\') return true;
    else if (c == '<')  return true;
    else if (c == '>')  return true;
    else if (c == '|')  return true;
    else if (c == '%')  return true;
    else                return false;
}
