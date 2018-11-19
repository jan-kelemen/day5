#include "operation_factory.h"

#include <stdexcept>

namespace fe
{
  std::size_t op_factory::register_creator(std::string const& id, creator_t creator)
  {
    if (creators_.find(id) != creators_.end())
      throw std::invalid_argument("already registered");

    creators_[id] = creator;
    return creators_.size();
  }

  std::unique_ptr<fe::operation> fe::op_factory::operator()(std::string const& id) const
  {
    return creators_.at(id)();
  }

  static auto counter = 0;
  static std::aligned_storage<sizeof(op_factory), alignof(op_factory)>::type factory_buffer;
  op_factory& operation_factory = reinterpret_cast<op_factory&>(factory_buffer);

  op_factory_init::op_factory_init() { if (counter++ == 0) new (&operation_factory) op_factory(); }
  op_factory_init::~op_factory_init() { if (--counter == 0) (&operation_factory)->~op_factory(); }
}


