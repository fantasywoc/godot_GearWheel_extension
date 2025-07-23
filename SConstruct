#!/usr/bin/env python
import os
import sys

from methods import print_error

# 库文件名
libname = "EXTENSION-VERLET"
# libname = "EXTENSION-NAME"
# 项目路径
projectdir = "demo"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Add(EnumVariable('float_precision', 'Floating point precision (single or double)', 'single', 
                      allowed_values=('single', 'double')))
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

# 添加浮点精度配置
float_precision = env['float_precision']
if float_precision == 'double':
    env.Append(CPPDEFINES=['DOUBLE_PRECISION=1'])
    print("Building with DOUBLE precision")
else:
    env.Append(CPPDEFINES=['SINGLE_PRECISION=1'])
    print("Building with SINGLE precision")

# 添加构建类型配置
if env["target"] == "release":
    env.Append(CCFLAGS=['-O3'])
    print("Building RELEASE version")
else:
    env.Append(CCFLAGS=['-g'])
    print("Building DEBUG version")

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

# 添加精度标识到文件名
if float_precision == 'double':
    suffix += ".double"

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources,
)

copy = env.Install("{}/bin/{}/".format(projectdir, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)