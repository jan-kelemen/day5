#pragma once

#include <iosfwd>

#include "block.h"

namespace fe
{
  class block_sequence
  {
  public:
    using block_iterator = std::vector<block>::const_iterator;

    block_sequence() = default;
    explicit block_sequence(std::vector<block> blocks);
    block_sequence(block_sequence const&) = default;
    block_sequence(block_sequence&&) = default;

    std::size_t size() const;
    std::pair<block_iterator, block_iterator> blocks() const;    

    void add(block block);
    void move_to_beginning(std::size_t index);
    void remove(std::size_t index);

    double operator()(double arg) const;

    block const& operator[](std::size_t index) const;

    block_sequence& operator=(block_sequence const&) = default;
    block_sequence& operator=(block_sequence&&) = default;

    ~block_sequence() = default;
  private:
    std::vector<block> blocks_;
  };

  std::ostream& operator<<(std::ostream& stream, block_sequence const& sequence);
}