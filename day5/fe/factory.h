#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace fe
{
  template<typename T>
  class factory
  {
  public:
    using creator_t = std::function<std::unique_ptr<T>()>;

    std::size_t register_creator(std::string const& id, creator_t creator);
    std::unique_ptr<T> operator()(std::string const& id) const;
    std::vector<std::string> registered_ids() const;

    virtual ~factory() = default;
  private:
    std::map<std::string, creator_t, std::less<>> creators_;
  };

  template<typename T>
  std::size_t factory<T>::register_creator(std::string const& id, creator_t creator)
  {
    if (creators_.find(id) != creators_.end())
      throw std::invalid_argument("already registered");

    creators_[id] = creator;
    return creators_.size();
  }

  template<typename T>
  std::unique_ptr<T> factory<T>::operator()(std::string const& id) const
  {
    return creators_.at(id)();
  }

  template<typename T>
  std::vector<std::string> factory<T>::registered_ids() const
  {
    auto rv = std::vector<std::string>();
    rv.reserve(creators_.size());

    std::transform(creators_.cbegin(), creators_.cend(), std::back_inserter(rv), [](const auto& pair) { return pair.first; });

    return rv;
  }
}