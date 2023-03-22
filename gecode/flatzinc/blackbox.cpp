#include <gecode/int.hh>
#include <iostream>
#include <dlfcn.h>

#include <gecode/flatzinc/blackbox.hh>

namespace Gecode { namespace FlatZinc {
        void
        blackbox(Home home, const IntVarArgs& xv, const IntVarArgs& yv){
            ViewArray<Int::IntView> x(home,xv);
            ViewArray<Int::IntView> y(home,yv);

            if (home.failed())
                return;
            PostInfo pi(home);
            GECODE_ES_FAIL(Gecode::FlatZinc::BlackBox::post(home, x, y));
        }

        // The x(x0), and y(y0) initialise the values
        // How should I be naming the x0 and y0?
        // How should we pass in the dll file path?
        BlackBox::BlackBox(Home home, ViewArray<Int::IntView>& x0, ViewArray<Int::IntView>& y0) : Propagator(home), x(x0), y(y0) {
            // We will make the path a variable that is passed in, in future
            bbFunctionContainer = new Gecode::FlatZinc::PluginContainer("/Users/kevin/Projects/gecode/dll/square.so");

            x.subscribe(home, *this, Int::PC_INT_VAL);
        }
        // Constructor for cloning
        // What does calling Propagator(home, p) do ? Is the same as `super` in Java
        // Do we actually need to do x(p.x) and y(p.y)? why does it work without them, is the super class call initilising them?
        BlackBox::BlackBox(Space &home, BlackBox& p) : Propagator(home, p), bbFunctionContainer(p.bbFunctionContainer) {
            // How does this bit of code clone the BlackBox object?
            // What does this update function do?
            x.update(home, p.x);
            y.update(home, p.y);
        }
        // Cost function (defined as low linear)
        PropCost BlackBox::cost(const Space& home, const ModEventDelta& med) const {
            return PropCost::binary(PropCost::LO);
        };
        // Schedule function
        void
        BlackBox::reschedule(Space& home){
            x.cancel(home, *this, Int::PC_INT_VAL);
            y.cancel(home, *this, Int::PC_INT_VAL);
        };

        size_t BlackBox::dispose(Space& home){
            x.cancel(home, *this, Int::PC_INT_VAL);
            (void)Propagator::dispose(home);
            // destroy plugin container
            bbFunctionContainer->~PluginContainer();
            return sizeof(*this);
        };

        ExecStatus BlackBox::propagate(Space &home, const ModEventDelta &){
            if (x.assigned()){
                std::vector<int> in = std::vector<int>(x.size());
                std::vector<int> out = std::vector<int>(y.size());
                for (int i=0; i < in.size(); i++){
                    in[i] = x[i].val();
                }
                PluginBase* pb = bbFunctionContainer->instance();
                // Are dll calls blocking?
                pb -> run(in, out);

                for (int i=0; i < out.size(); i++){
                    if (y[i].eq(home, out[i]) == Int::ME_INT_FAILED){
                        return ES_FAILED;
                    }
                }
                return ES_SUBSUMED_;
            }
            return ES_NOFIX;
        };

        ExecStatus BlackBox::post(Home home, ViewArray<Int::IntView>& x, ViewArray<Int::IntView>& y){
            new (home) BlackBox(home,x,y);
            return ES_OK;
        }

        Propagator* BlackBox::copy(Space &home) {
            return new (home) BlackBox(home, *this);
        }
    }
}