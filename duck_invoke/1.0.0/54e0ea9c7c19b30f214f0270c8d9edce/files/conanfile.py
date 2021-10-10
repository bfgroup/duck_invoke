'''
@author: René Ferdinand Rivera Morell
@copyright: Copyright René Ferdinand Rivera Morell 2021
@license:
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
'''
from conans import ConanFile, tools
import os


class Package(ConanFile):
    name = "duck_invoke"
    homepage = "https://www.bfgroup.xyz/duck_invoke/"
    description = '''A simple to use, single header, tag_invoke utility for C++11.'''
    topics = ("header", 'header-only', "cross-platform", "c++11", "tag_invoke")
    license = "BSL-1.0"
    url = "https://github.com/bfgroup/duck_invoke"
    barbarian = {
        "description": {"format": "asciidoc", "file": "README_CONAN.adoc"}
    }
    exports = "README_CONAN.adoc"
    source_subfolder = "source_subfolder"

    def source(self):
        tools.get(
            **self.conan_data["sources"][self.version],
            strip_root=True, destination=self.source_subfolder)

    no_copy_source = True

    def package_id(self):
        self.info.header_only()

    def package(self):
        self.copy(
            pattern="LICENSE.txt", dst="licenses",
            src=self.source_subfolder)
        for pattern in ["*.h", "*.hpp", "*.hxx"]:
            self.copy(
                pattern=pattern, dst="include",
                src=os.path.join(self.source_subfolder, "include"))
