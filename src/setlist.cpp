// Copyright 2024 Kushview, LLC <info@kushview.net>
// SPDX-License-Identifier: GPL-3

#include <cmath>
#include <cstdint>
#include <vector>

#include <lvtk/lvtk.hpp>
#include <lvtk/plugin.hpp>

#include "setlist.hpp"

class SetList : public lvtk::Plugin<SetList> {
public:
    SetList (const lvtk::Args& args) 
        : Plugin (args) {
    }

    void connect_port (uint32_t port, void* data) {
        lvtk::ignore (port, data);
    }

    void run (uint32_t nframes) {
        lvtk::ignore (nframes);
    }
};

static const lvtk::Descriptor<SetList> sSetList (KV_SETLIST_URI);
