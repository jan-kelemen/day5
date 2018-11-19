#include "action.h"

namespace fe
{
  std::string const& action::id() const { return id_; }
  std::string const & action::name() const { return name_; }
  action::action(std::string id, std::string name)
    : id_{std::move(id)}
    , name_{std::move(name)}
  {
    ;
  }
}
