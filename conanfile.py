from conan import ConanFile

class MainProject(ConanFile):
    python_requires = "conan_template/[^5.0.6]@robotkernel/stable"
    python_requires_extend = "conan_template.RobotkernelConanFile"

    name = "module_vtun"
    description = "robotkernel-5 is a modular, easy configurable hardware abstraction framework"
    exports_sources = ["*", "!.gitignore"]
    requires = ["robotkernel/[~=5]@robotkernel/stable", ] 
