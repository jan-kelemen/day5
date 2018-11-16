#pragma once

#include <functional>
#include <map>
#include <memory>

template<typename T>
class factory
{
public:
  using creator_t = std::function<std::unique_ptr<T>(std::string_view)>;

  static int register_creator(std::string_view id, creator_t creator);
  std::unique_ptr<T> operator()(std::string_view id) const;

private:
  static std::map<std::string, creator_t, std::less<>> creators_;
};

template<typename T>
int factory<T>::register_creator(std::string_view id, creator_t creator)
{
  creators_[id] = creator;
  return creators_.size();
}

template <typename T>
std::unique_ptr<T> factory<T>::operator()(std::string_view id) const
{
  return creators_.at(id)();
}
