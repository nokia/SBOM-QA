from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.build import check_min_cppstd


class CppTemplate(ConanFile):
    generators = 'CMakeToolchain', 'CMakeDeps'
    settings = 'os', 'arch', 'compiler', 'build_type'

    requires = 'cppfront/cci.20231017', 'fmt/9.0.0'

    def validate(self):
        if self.info.settings.compiler.cppstd:
            check_min_cppstd(self, "20")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

