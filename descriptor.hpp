#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <string>
#include <stdexcept>

inline std::string parseTypeDescriptor(const std::string &descriptor, size_t &position)
{
    size_t arrayDimensions = 0;
    while (position < descriptor.size() && descriptor[position] == '[')
    {
        ++arrayDimensions;
        ++position;
    }

    if (position >= descriptor.size())
        throw std::runtime_error("Exibidor: descriptor invalido");

    std::string baseType;
    char current = descriptor[position++];
    switch (current)
    {
    case 'B': baseType = "byte";    break;
    case 'C': baseType = "char";    break;
    case 'D': baseType = "double";  break;
    case 'F': baseType = "float";   break;
    case 'I': baseType = "int";     break;
    case 'J': baseType = "long";    break;
    case 'S': baseType = "short";   break;
    case 'Z': baseType = "boolean"; break;
    case 'V': baseType = "void";    break;
    case 'L':
    {
        size_t end = descriptor.find(';', position);
        if (end == std::string::npos)
            throw std::runtime_error("Exibidor: descriptor de referencia invalido");
        baseType = descriptor.substr(position, end - position);
        position = end + 1;
        break;
    }
    default:
        throw std::runtime_error("Exibidor: tipo de descriptor desconhecido");
    }

    for (size_t i = 0; i < arrayDimensions; ++i)
        baseType += "[]";

    return baseType;
}

inline std::string formatMethodParameters(const std::string &descriptor)
{
    size_t openParen  = descriptor.find('(');
    size_t closeParen = descriptor.find(')');
    if (openParen == std::string::npos || closeParen == std::string::npos || closeParen < openParen)
        throw std::runtime_error("Exibidor: assinatura de metodo invalida");

    std::string result;
    size_t position = openParen + 1;
    bool first = true;

    while (position < closeParen)
    {
        std::string type = parseTypeDescriptor(descriptor, position);
        if (!first) result += ", ";
        result += type;
        first = false;
    }

    return result;
}

inline std::string formatMethodReturnType(const std::string &descriptor)
{
    size_t closeParen = descriptor.find(')');
    if (closeParen == std::string::npos || closeParen + 1 >= descriptor.size())
        throw std::runtime_error("Exibidor: tipo de retorno invalido");

    size_t position = closeParen + 1;
    return parseTypeDescriptor(descriptor, position);
}

inline std::string formatFieldType(const std::string &descriptor)
{
    size_t position = 0;
    std::string type = parseTypeDescriptor(descriptor, position);
    if (position != descriptor.size())
        throw std::runtime_error("Exibidor: descriptor de campo invalido");
    return type;
}

#endif // DESCRIPTOR_HPP
