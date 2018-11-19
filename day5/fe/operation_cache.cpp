#include "operation_cache.h"

namespace fe
{
  operation_cache::operation_cache()
  {
    auto registered_ids = operation_factory.registered_ids();
    for(auto const& id : registered_ids)
    {
      auto operation = operation_factory(id);
      auto operation_name = operation->name();
      cached_operations_[operation_name] = std::move(operation);
      cached_names_.emplace_back(std::move(operation_name));
    }
  }

  std::pair<operation_cache::name_iterator, operation_cache::name_iterator> operation_cache::names() const
  {
    return std::make_pair(cached_names_.cbegin(), cached_names_.cend());
  }

  std::shared_ptr<operation const> operation_cache::operator()(std::string const& name) const
  {
    return cached_operations_.at(name);
  }
}


