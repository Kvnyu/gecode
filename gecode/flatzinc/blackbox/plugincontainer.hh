#ifndef PLUGINCONTAINER_H
#define PLUGINCONTAINER_H

#include <vector>
#include <string>
#include <type_traits>

namespace Gecode { namespace FlatZinc {
  using FunctionPtr = std::add_pointer<void(int*, int, int*, int)>::type;
  class PluginContainer {
  public:
    PluginContainer(const std::string& path);
    ~PluginContainer();
    void runBlackboxFunction(int* in, int length_in, int* out , int length_out);
  private:
    FunctionPtr blackboxFunctionPtr;
    void* _library;
  };
}}

#endif // PLUGINCONTAINER_H
