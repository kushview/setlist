
setlist_sources = files ('''
    setlist.cpp
'''.split())

setlist_ui_type = 'X11UI'
if host_machine.system() == 'windows'
    setlist_ui_type = 'WindowsUI'
elif host_machine.system() == 'darwin'
    setlist_ui_type = 'CocoaUI'
endif

plugin = shared_module ('setlist',
    setlist_sources,
    name_prefix : '',
    dependencies : [ lvtk_dep ],
    link_args : [ nodelete_cpp_link_args ],
    install : true,
    install_dir : lv2_install_dir,
    gnu_symbol_visibility : 'hidden'
)

ui = shared_module ('setlist-ui',
    'setlist-ui.cpp',
    name_prefix : '',
    dependencies : [ lvtk_cairo_dep ],
    include_directories : [ '.' ],
    link_args : [ nodelete_cpp_link_args ],
    install : true,
    install_dir : lv2_install_dir,
    cpp_args : [ ],
    gnu_symbol_visibility : 'hidden'
)

manifest_ttl = configure_file (
    input : 'manifest.ttl.in',
    output : 'manifest.ttl',
    configuration : {
        'BINARY' : fs.name (plugin.full_path()),
        'UI_BINARY' : fs.name (ui.full_path()),
        'UI_TYPE' : setlist_ui_type
    },
    install : true,
    install_dir : lv2_install_dir
)

foreach plug : [ 'setlist' ]
    plugin_ttl = configure_file (
        input : 'setlist.ttl.in',
        output : 'setlist.ttl',
        copy : true,
        install : true,
        install_dir : lv2_install_dir
    )

    if lv2_validate.found()
        test ('lv2_validate', lv2_validate, args : [ manifest_ttl, plugin_ttl ])
    endif
endforeach
