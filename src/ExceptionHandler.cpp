#include "../header/ExceptionHandler.hpp"

ExceptionHandler::ExceptionHandler(){}


ExceptionHandler::ExceptionHandler(u2 start_pc, u2 end_pc, u2 handler_pc, u2 catch_type){

    this->start_pc = start_pc;
    this->end_pc = end_pc;
    this->handler_pc = handler_pc;
    this->catch_type = catch_type;
}

