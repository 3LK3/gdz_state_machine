#!/usr/bin/env python
import os
import sys


# Settings
#
project_name = "gdz_state_machine"
addons_path = "./project/addons"
godot_cpp_path = "./godot-cpp"

addon_path = "{}/{}".format(addons_path, project_name)


# Build definition
#
env = SConscript("{}/SConstruct".format(godot_cpp_path))

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# Scons cache
scons_cache_path = os.environ.get("SCONS_CACHE")
if scons_cache_path != None:
    CacheDir(scons_cache_path)
    print("Scons cache enabled... (path: '" + scons_cache_path + "')")

# Docs
if env["target"] in ["editor", "template_debug"]:
    doc_data = env.GodotCPPDocData(
        f"src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml")
    )
    sources.append(doc_data)
    
debug_or_release = "release" if env["target"] == "template_release" else "debug"

library = env.SharedLibrary(
    "{}/bin/lib{}.{}.{}.{}{}".format(
        addon_path,
        project_name,
        env["platform"],
        debug_or_release,
        env["arch"],
        env["SHLIBSUFFIX"]
    ), 
    source=sources,
)

Default(library)