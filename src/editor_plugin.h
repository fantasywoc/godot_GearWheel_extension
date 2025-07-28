#ifndef EDITOR_PLUGIN_H
#define EDITOR_PLUGIN_H

#include <godot_cpp/classes/editor_plugin.hpp>

using namespace godot;

class ExampleClassEditorPlugin : public EditorPlugin {
    GDCLASS(ExampleClassEditorPlugin, EditorPlugin);

public:
    ExampleClassEditorPlugin();
    ~ExampleClassEditorPlugin() override;

    bool _has_main_screen() const override { return false; } // 插件无需主界面，返回 false
    void _enter_tree() override;
    void _exit_tree() override;
};

#endif