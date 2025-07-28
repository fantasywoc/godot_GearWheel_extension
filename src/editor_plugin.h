#ifndef EDITOR_PLUGIN_H
#define EDITOR_PLUGIN_H

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/editor_inspector_plugin.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class RotatableInspectorPlugin : public EditorInspectorPlugin {
    GDCLASS(RotatableInspectorPlugin, EditorInspectorPlugin);

protected:
    static void _bind_methods() {}

public:
    // 修正：匹配父类函数签名
    virtual bool _can_handle(Object *p_object) const override;
    virtual void _parse_category(Object *p_object, const String &p_category) override;
};

class RotatableEditorPlugin : public EditorPlugin {
    GDCLASS(RotatableEditorPlugin, EditorPlugin);

private:
    Ref<RotatableInspectorPlugin> inspector_plugin;

protected:
    static void _bind_methods() {}

public:
    RotatableEditorPlugin();
    ~RotatableEditorPlugin() override;

    virtual bool _has_main_screen() const override { return false; }
    virtual void _enter_tree() override;
    virtual void _exit_tree() override;
};

#endif // EDITOR_PLUGIN_H