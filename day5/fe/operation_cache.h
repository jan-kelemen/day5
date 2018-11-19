#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "operation_factory.h"

namespace fe
{
  class operation_cache
  {
  public:
    using name_iterator = std::vector<std::string>::const_iterator;

    operation_cache();
    operation_cache(operation_cache const&) = delete;
    operation_cache(operation_cache&&) = default;

    std::pair<name_iterator, name_iterator> names() const;
    std::shared_ptr<operation const> operator()(std::string const& name) const;

    operation_cache& operator=(operation_cache const&) = delete;
    operation_cache& operator=(operation_cache&&) = default;

    ~operation_cache() = default;
  private:
    std::unordered_map<std::string, std::shared_ptr<operation const>> cached_operations_;
    std::vector<std::string> cached_names_;
  };
}