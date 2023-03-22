// The plugin base file needs to get put into our path Gecode so that it can be found 
#include <iostream>
#include <gecode/flatzinc/plugin.hh>
#include "plugin_base.hh"

class Square : public Gecode::FlatZinc::PluginBase {
public:
  Square() : PluginBase("Implementation of Square function") {};
  void run(std::vector<int>& in, std::vector<int>& out) { 
    for(int i=0; i < in.size(); i++){
      out[i] = in[i] * in[i];
    }
  };
};

extern "C" Gecode::FlatZinc::PluginBase* plugin_create() {
  return new Square;
}

extern "C" void plugin_destroy(Gecode::FlatZinc::PluginBase* square) {
  delete square;
}
