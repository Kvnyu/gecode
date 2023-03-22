#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <string>

namespace Gecode { namespace FlatZinc {
  class PluginBase {
  public:
    PluginBase(const std::string name) : _name(name) {};
    // This is ones bitwise not, it is the destructor
    virtual ~PluginBase() {};
    virtual std::string& getName() { return _name; };
    virtual void run(std::vector<int>& in, std::vector<int>& out) = 0;
  private:
    std::string _name;
  };

  typedef PluginBase* (*plugin_create_t)();
  typedef void (*plugin_destroy_t)(PluginBase*);
  }
}


#endif // INTERFACE_H
