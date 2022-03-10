#ifndef __ExceptionTable_HPP__
#define __ExceptionTable_HPP__

#include "Dados.hpp"

class ExceptionHandler
{
public:
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
    ExceptionHandler(u2 start_pc, u2 end_pc, u2 handler_pc, u2 catch_type);
};

#endif