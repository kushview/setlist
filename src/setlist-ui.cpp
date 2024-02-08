// Copyright 2024 Kushview, LLC <info@kushview.net>
// SPDX-License-Identifier: GPL-3

#include <algorithm>
#include <iostream>

#include <lvtk/ext/idle.hpp>
#include <lvtk/ext/parent.hpp>
#include <lvtk/ext/resize.hpp>
#include <lvtk/lvtk.h>
#include <lvtk/options.hpp>
#include <lvtk/ui.hpp>

#include <lvtk/ui/main.hpp>
#include <lvtk/ui/cairo.hpp>
#include <lvtk/ui/widget.hpp>

#include <lvtk/ext/urid.hpp>
#include <lvtk/weak_ref.hpp>

#include "setlist.hpp"

using namespace lvtk;


class ProgramTable : public lvtk::Widget {
public:
    ProgramTable() { 
        set_name ("ProgramTable");
    }

    int num_items() {
        return 2;
    }
};

class SetListUI final : public UI<SetListUI, Parent, Idle, URID, Options> {
public:
    SetListUI (const UIArgs& args)
        : UI (args) {
        for (const auto& opt : OptionArray (options())) {
            if (opt.key == map_uri (LV2_UI__scaleFactor))
                scale_factor = *(float*) opt.value;
        }
    }

    void cleanup() {
        content.reset();
    }

    int idle() {
        _main.loop (0);
        return 0;
    }

    void port_event (uint32_t port, uint32_t size,
                     uint32_t format, const void* buffer) {}

    LV2UI_Widget widget() {
        if (content == nullptr) {
            content = std::make_unique<Content>();
            content->set_size (360, 240);
            content->set_visible (true);
            _main.elevate (*content, 0, (uintptr_t) parent.get());
        }

        return *content;
    }

private:
    lvtk::Main _main { lvtk::Mode::MODULE, std::make_unique<lvtk::Cairo>() };

    class Content : public Widget {
    public:
        Content() {
            set_name ("SetListUI::Content");
            set_size (360, 240);
            set_visible (true);
            set_opaque (true);
        }

        ~Content() {
        }

        void motion (const Event& ev) override {
            // std::clog << "volume content motion\n";
        }

        void resized() override {}

        void paint (Graphics& g) override {
            g.set_color (Color (0xff545454));
            g.fill_rect (bounds().at (0, 0).as<float>());
        }
    };
    
    std::unique_ptr<Widget> content;
    float scale_factor { 1.f };
};

static UIDescriptor<SetListUI> sSetListUI (
    KV_SETLIST_UI_URI, {});
