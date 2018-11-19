#include "action_cache.h"

namespace fe
{
  action_cache::action_cache()
  {
    auto registered_ids = action_factory.registered_ids();
    for (auto const& id : registered_ids)
    {
      auto action = action_factory(id);
      auto action_name = action->name();
      cached_actions_[action_name] = std::move(action);
      cached_names_.emplace_back(std::move(action_name));
    }
  }

  std::pair<action_cache::name_iterator, action_cache::name_iterator> action_cache::names() const
  {
    return std::make_pair(cached_names_.cbegin(), cached_names_.cend());
  }

  std::shared_ptr<action const> action_cache::operator()(std::string const& name) const
  {
    return cached_actions_.at(name);
  }
}


