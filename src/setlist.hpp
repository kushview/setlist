#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define KV_SETLIST_URI    "https://kushview.net/plugins/setlist"
#define KV_SETLIST_UI_URI KV_SETLIST_URI "/ui"

struct Program {
    uint8_t program { 0 };
    std::string name;
    float tempo {120.0 };
};

class Programs final {
public:
    using size_type = std::vector<Program>::size_type;
    using value_type = std::vector<Program>::value_type;

    Programs() {
        _progs.reserve (128);
        _progs.assign (128, {});
        update_program_numbers();
    }

    ~Programs() {
        _progs.clear();
        _progs.shrink_to_fit();
    }

    Programs (const Programs& o) { operator= (o); }
    Programs& operator= (const Programs& o) {
        _progs.clear();
        for (const auto& p : o._progs)
            _progs.push_back (p);
        return *this;
    }

    Programs (Programs&& o) { operator= (std::forward<Programs> (o)); }
    Programs& operator= (Programs&& o) {
        _progs = std::move (o._progs);
        return *this;
    }

    void add (std::string_view name, float tempo) {
        auto& ref = _progs.at (_size);
        ref.name = name;
        ref.tempo = tempo;
        ref.program = static_cast<uint8_t> (_size);
        ++_size;
    }

    void clear() noexcept { _size = 0; }
    auto size() const noexcept { return _size; }
    auto at (size_type index) noexcept { return _progs.at (index); }

private:
    std::vector<Program> _progs;
    size_type _size { 0 };
    void update_program_numbers() noexcept {
        uint8_t i = 0;
        for (auto& prog : _progs)
            prog.program = i++;
    }
};
