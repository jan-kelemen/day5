#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "action_factory.h"

namespace fe
{
  class action_cache
  {
  public:
    using name_iterator = std::vector<std::string>::const_iterator;

    action_cache();
    action_cache(action_cache const&) = delete;
    action_cache(action_cache&&) = default;

    std::pair<name_iterator, name_iterator> names() const;
    std::shared_ptr<action const> operator()(std::string const& name) const;

    action_cache& operator=(action_cache const&) = delete;
    action_cache& operator=(action_cache&&) = default;

    ~action_cache() = default;
  private:
    std::unordered_map<std::string, std::shared_ptr<action const>> cached_actions_;
    std::vector<std::string> cached_names_;
  };
}