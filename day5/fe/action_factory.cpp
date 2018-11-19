#include "action_factory.h"

namespace fe
{
  static auto counter = 0;
  static std::aligned_storage<sizeof(act_factory), alignof(act_factory)>::type factory_buffer;
  act_factory& action_factory = reinterpret_cast<act_factory&>(factory_buffer);

  act_factory_init::act_factory_init() { if (counter++ == 0) new (&action_factory) act_factory(); }
  act_factory_init::~act_factory_init() { if (--counter == 0) (&action_factory)->~act_factory(); }
}
