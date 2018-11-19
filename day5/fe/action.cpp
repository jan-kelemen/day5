#include "action.h"

#include <fstream>
#include <iterator>
#include <filesystem>
#include <string>

#include "action_factory.h"

namespace fe
{
  std::string const& action::id() const { return id_; }
  std::string const & action::name() const { return name_; }

  action::action(std::string id, std::string name)
    : id_{ std::move(id) }
    , name_{ std::move(name) }
  {
    ;
  }

  class add_block : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{E1DF2B61-F490-4A8D-8F63-8D96216A6575}";

    add_block() : action(registration_id, "add block") {}

    add_block(add_block const&) = default;
    add_block(add_block&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    add_block& operator=(add_block const&) = default;
    add_block& operator=(add_block&&) = default;

    virtual ~add_block() = default;    
  };

  std::size_t add_block::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<add_block>(); });

  void add_block::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    using namespace std::string_literals;
    ostream << "Enter operation name and parameters (e.g. \"limit 2 3\"):\n";
    auto name = ""s;
    istream >> name;
    auto operation = cache(name);
    auto params = std::vector<double>();
    std::copy_n(std::istream_iterator<double>(istream), operation->argument_count(), std::back_inserter(params));
    sequence.add(block(params, operation));
    ostream << "Block added successfully\n";
  }

  class remove_block : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{E58FB622-4FB3-4DB6-A477-009DD98961FE}";

    remove_block() : action(registration_id, "remove block") {}

    remove_block(remove_block const&) = default;
    remove_block(remove_block&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    remove_block& operator=(remove_block const&) = default;
    remove_block& operator=(remove_block&&) = default;

    virtual ~remove_block() = default;
  };

  std::size_t remove_block::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<remove_block>(); });

  void remove_block::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    ostream << "Enter index of block to remove from sequence [0, size):\n";
    auto index = std::size_t{};
    istream >> index;
    sequence.remove(index);
    ostream << "Block removed successfully\n";
  }

  class set_first_block : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{19DD9108-1EE6-4D0F-A32C-B8540A895632}";

    set_first_block() : action(registration_id, "set first block") {}

    set_first_block(set_first_block const&) = default;
    set_first_block(set_first_block&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    set_first_block& operator=(set_first_block const&) = default;
    set_first_block& operator=(set_first_block&&) = default;

    virtual ~set_first_block() = default;
  };

  std::size_t set_first_block::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<set_first_block>(); });

  void set_first_block::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    ostream << "Enter index of block to move to the first place [0, size):\n";
    auto index = std::size_t{};
    istream >> index;
    sequence.move_to_beginning(index);
    ostream << "Block moved successfully\n";
  }

  class show_sequence : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{E636335A-D0AB-46A2-A9B4-039011B64B69}";

    show_sequence() : action(registration_id, "show sequence") {}

    show_sequence(show_sequence const&) = default;
    show_sequence(show_sequence&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    show_sequence& operator=(show_sequence const&) = default;
    show_sequence& operator=(show_sequence&&) = default;

    virtual ~show_sequence() = default;
  };

  std::size_t show_sequence::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<show_sequence>(); });

  void show_sequence::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    ostream << "Sequence:\n";
    auto const&[begin, end] = sequence.blocks();
    for (auto i = std::size_t{ 0 }; i != sequence.size(); ++i)
      ostream << '\t' << sequence[i] << '\n';
  }

  class execute_sequence : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{F4FAD162-D8BC-46B9-821B-4AE407C42C7C}";

    execute_sequence() : action(registration_id, "execute sequence") {}

    execute_sequence(execute_sequence const&) = default;
    execute_sequence(execute_sequence&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    execute_sequence& operator=(execute_sequence const&) = default;
    execute_sequence& operator=(execute_sequence&&) = default;

    virtual ~execute_sequence() = default;
  };

  std::size_t execute_sequence::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<execute_sequence>(); });

  void execute_sequence::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    ostream << "Enter initial value:\n";
    auto initial = 0.;
    istream >> initial;
    ostream << "Result: " << sequence(initial) << '\n';
  }

  class execute_file_sequence : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{2E28296F-8D2E-4410-92C6-A47241FEBA93}";

    execute_file_sequence() : action(registration_id, "execute file sequence") {}

    execute_file_sequence(execute_file_sequence const&) = default;
    execute_file_sequence(execute_file_sequence&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    execute_file_sequence& operator=(execute_file_sequence const&) = default;
    execute_file_sequence& operator=(execute_file_sequence&&) = default;

    virtual ~execute_file_sequence() = default;
  };

  std::size_t execute_file_sequence::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<execute_file_sequence>(); });

  void execute_file_sequence::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    using namespace std::string_literals;
    namespace fs = std::filesystem;
    ostream << "Enter name of the file with input values and name of the file with output values (e.g. input.txt output.txt):\n";
    auto input = ""s, output = ""s;
    istream >> input >> output;

    auto input_path = absolute(fs::path(input));
    auto output_path = absolute(fs::path(output));

    if (!exists(input_path))
    {
      ostream << "Input file doesn't exist\n";
      return;
    }
      
    auto input_stream = std::ifstream(input_path.c_str());
    auto output_stream = std::ofstream(output_path.c_str());

    std::transform(std::istream_iterator<double>(input_stream), std::istream_iterator<double>(), std::ostream_iterator<double>(output_stream), [&sequence](double v) { return sequence(v); });
    ostream << "Sequence executed successfully\n";
  }

  class store_sequence : public action
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{C7948CFB-F564-4B75-8242-833C544330FE}";

    store_sequence() : action(registration_id, "store sequence") {}

    store_sequence(store_sequence const&) = default;
    store_sequence(store_sequence&&) = default;

    void operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const override;

    store_sequence& operator=(store_sequence const&) = default;
    store_sequence& operator=(store_sequence&&) = default;

    virtual ~store_sequence() = default;
  };

  std::size_t store_sequence::factory_id = action_factory.register_creator(registration_id, []() { return std::make_unique<store_sequence>(); });

  void store_sequence::operator()(operation_cache const& cache, block_sequence& sequence, std::ostream& ostream, std::istream& istream) const
  {
    using namespace std::string_literals;
    namespace fs = std::filesystem;

    ostream << "Enter name of the file with input values and name of the file with output values (e.g. input.txt output.txt):\n";
    auto output = ""s;
    istream >> output;

    auto output_path = absolute(fs::path(output));
    auto output_stream = std::ofstream(output_path.c_str());

    auto const&[begin, end] = sequence.blocks();
    std::copy(begin, end, std::ostream_iterator<block>(output_stream));
  }
}
