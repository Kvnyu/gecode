#include "plugincontainer.hh"

#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <string>

namespace Gecode { namespace FlatZinc {
  PluginContainer::PluginContainer(const std::string& dll_path)
    : _library(0) {
    // We will make the path a variable that is passed in, in future
    std::cerr << "loading library " << dll_path << std::endl;
    void* _library;
    _library = dlopen(dll_path.c_str(), RTLD_LAZY);
    if (!_library)
        throw "error loading library\n" + std::string(dlerror());
    dlerror(); // reset errors;
    std::cerr << "loaded library " << dll_path << " succesfully" << std::endl;

    // load create function
    blackboxFunctionPtr = (Gecode::FlatZinc::FunctionPtr) dlsym(_library, "run_function");
    if (!blackboxFunctionPtr)
      std::cerr << "Couldn't load function: run_function" << std::endl;
      // throw std::string(dlerror());
  };

  PluginContainer::~PluginContainer() {
    if (_library)
      dlclose(_library);
  };

  void PluginContainer::runBlackboxFunction(int* in , int length_in, int* out, int length_out){
    (*blackboxFunctionPtr)(in, length_in, out, length_out);
  }
}
}

