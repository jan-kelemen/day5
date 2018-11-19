#include "block_sequence.h"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace fe
{
  block_sequence::block_sequence(std::vector<block> blocks)
    : blocks_{std::move(blocks)}
  {}

  std::size_t block_sequence::size() const { return blocks_.size(); }

  std::pair<block_sequence::block_iterator, block_sequence::block_iterator> block_sequence::blocks() const
  {
    return std::make_pair(blocks_.cbegin(), blocks_.cend());
  }

  void block_sequence::add(block block)
  {
    blocks_.emplace_back(std::move(block));
  }

  void block_sequence::move_to_beginning(std::size_t index)
  {
    if (index > blocks_.size())
      throw std::out_of_range("index out of range");

    auto block = blocks_[index];
    blocks_.insert(blocks_.begin(), std::move(block));
    blocks_.erase(blocks_.begin() + index + 1);
  }

  void block_sequence::remove(std::size_t index)
  {
    if (index > blocks_.size())
      throw std::out_of_range("index out of range");

    blocks_.erase(blocks_.begin());
  }

  double block_sequence::operator()(double arg) const
  {
    return std::accumulate(blocks_.cbegin(), blocks_.cend(), arg, [](double acc, block const& block) { return block(acc); });
  }

  block const& block_sequence::operator[](std::size_t index) const { return blocks_[index]; }

  std::ostream& operator<<(std::ostream& stream, block_sequence const& sequence)
  {
    auto const&[begin, end] = sequence.blocks();
    std::copy(begin, end, std::ostream_iterator<block>(stream));
    return stream;
  }

}
