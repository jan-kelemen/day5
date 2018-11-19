#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "operation.h"

namespace fe
{
  class op_factory
  {
  public:
    using creator_t = std::function<std::unique_ptr<operation>()>;

    std::size_t register_creator(std::string const& id, creator_t creator);
    std::unique_ptr<operation> operator()(std::string const& id) const;

  private:
    std::map<std::string, creator_t, std::less<>> creators_;
  };

  extern op_factory& operation_factory;
  
  //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter
  static struct op_factory_init
  {
    op_factory_init();
    op_factory_init(op_factory_init const&) = delete;
    op_factory_init(op_factory_init&&) = delete;
    op_factory_init& operator=(op_factory_init const&) = delete;
    op_factory_init& operator=(op_factory_init&&) = delete;
    ~op_factory_init();
  } operation_factory_initializer;
}