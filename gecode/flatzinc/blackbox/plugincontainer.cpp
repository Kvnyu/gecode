#include "plugincontainer.hh"

#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <string>

namespace Gecode { namespace FlatZinc {
  PluginContainer::PluginContainer(const std::string& path)
    : _library(0), _instance(0) {
    // load library
    std::cerr << "loading library " << path << std::endl;
    _library = dlopen(path.c_str(), RTLD_LAZY);
    if (!_library)
      throw std::string(dlerror());
    dlerror(); // reset errors;

    // load create function
    _create = (plugin_create_t)dlsym(_library, "plugin_create");
    const char* dlsym_error = dlerror();
    if (dlsym_error)
      throw std::string(dlerror());

    // load destroy function
    _destroy = (plugin_destroy_t)dlsym(_library, "plugin_destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
      throw std::string(dlerror());

    // create instance
    _instance = _create();
  };

  PluginContainer::~PluginContainer() {
    if (_instance)
      _destroy(_instance);
    if (_library)
      dlclose(_library);
  };

  PluginBase* PluginContainer::instance() {
    return _instance;
  }
}
}

