#pragma once

#include "operation.h"
#include "factory.h"

namespace fe
{
  class op_factory : public factory<operation>
  {
  };

  extern op_factory& operation_factory;
  
  //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter
  static struct op_factory_init
  {
    op_factory_init();
    op_factory_init(op_factory_init const&) = delete;
    op_factory_init(op_factory_init&&) = delete;
    op_factory_init& operator=(op_factory_init const&) = delete;
    op_factory_init& operator=(op_factory_init&&) = delete;
    ~op_factory_init();
  } operation_factory_initializer;
}