#include <iostream>
#include <string>

#include "operation_cache.h"
#include "action_cache.h"

void print_action_names(fe::action_cache const& act_cache);

int main()
{
  using namespace std::string_literals;

  auto line = ""s;
  auto op_cache = fe::operation_cache();
  auto act_cache = fe::action_cache();
  auto sequence = fe::block_sequence();
  while(line != "exit")
  {
    try
    {
      std::cout << "Enter name of the action to execute:\n";
      print_action_names(act_cache);
      std::getline(std::cin, line);
      if (line == "exit") break;
      auto const& action = act_cache(line);
      (*action)(op_cache, sequence, std::cout, std::cin);
      std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    catch(std::exception& e)
    {
      std::cout << e.what();
    }
  }
}

void print_action_names(fe::action_cache const& act_cache)
{
  auto const&[begin, end] = act_cache.names();
  std::for_each(begin, end, [](auto const& name) { std::cout << '\t' << name << '\n'; });
}
