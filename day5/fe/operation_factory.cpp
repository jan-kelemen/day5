#include "operation_factory.h"

namespace fe
{
  static auto counter = 0;
  static std::aligned_storage<sizeof(op_factory), alignof(op_factory)>::type factory_buffer;
  op_factory& operation_factory = reinterpret_cast<op_factory&>(factory_buffer);

  op_factory_init::op_factory_init() { if (counter++ == 0) new (&operation_factory) op_factory(); }
  op_factory_init::~op_factory_init() { if (--counter == 0) (&operation_factory)->~op_factory(); }
}


