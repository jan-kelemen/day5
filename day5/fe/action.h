#pragma once

#include <iosfwd>
#include <string>

#include "block_sequence.h"

namespace fe
{
  class action
  {
  public:
    action() = delete;
    action(action const&) = default;
    action(action&&) = default;

    std::string const& id() const;
    std::string const& name() const;
    virtual void operator()(block_sequence& sequence, std::ostream& ostream, std::istream& istream) const = 0;

    action& operator=(action const&) = default;
    action& operator=(action&&) = default;

    virtual ~action() = default;
  protected:
    action(std::string id, std::string name);
  private:
    std::string id_{};
    std::string name_{};
  };
}