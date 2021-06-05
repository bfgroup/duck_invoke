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


required_conan_version = ">=1.32.0"


class DuckInvokeConan(ConanFile):
    name = "duck_invoke"
    homepage = "https://www.bfgroup.xyz/duck_invoke/"
    description = '''A simple to use, single header, tag_invoke utility for C++11.'''
    topics = ("header", 'header-only', "cross-platform", "c++11")
    license = "BSL-1.0"
    no_copy_source = True
    url = "https://github.com/bfgroup/duck_invoke"
    source_subfolder = "source_subfolder"

    def source(self):
        tools.get(**self.conan_data["sources"][self.version],
                  strip_root=True, destination=self.source_subfolder)

    def package(self):
        self.copy(pattern="LICENSE.txt", dst="licenses",
                  src=self.source_subfolder)
        self.copy(pattern="*.h", dst="include",
                  src=os.path.join(self.source_subfolder, "include"))

    def package_id(self):
        self.info.header_only()
