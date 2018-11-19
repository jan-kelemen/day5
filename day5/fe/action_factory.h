#pragma once

#include "action.h"
#include "factory.h"

namespace fe
{
  class act_factory : public factory<action>
  {};

  extern act_factory& action_factory;

  //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter
  static struct act_factory_init
  {
    act_factory_init();
    act_factory_init(act_factory_init const&) = delete;
    act_factory_init(act_factory_init&&) = delete;
    act_factory_init& operator=(act_factory_init const&) = delete;
    act_factory_init& operator=(act_factory_init&&) = delete;
    ~act_factory_init();
  } action_factory_initializer;
}