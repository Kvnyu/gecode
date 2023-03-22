#ifndef PLUGINCONTAINER_H
#define PLUGINCONTAINER_H

#include "plugin_base.hh"

namespace Gecode { namespace FlatZinc {
  class PluginContainer {
  public:
    PluginContainer(const std::string& path);
    ~PluginContainer();
    Gecode::FlatZinc::PluginBase* instance();
  private:
    void* _library;
    Gecode::FlatZinc::plugin_create_t _create;
    Gecode::FlatZinc::plugin_destroy_t _destroy;
    Gecode::FlatZinc::PluginBase* _instance;
  };
}}

#endif // PLUGINCONTAINER_H
