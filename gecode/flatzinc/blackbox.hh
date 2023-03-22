// We could also introduce a new template with two view arrays?
// Later we can do below to allow for other types of views like float etc
// template<class view>
#include <gecode/flatzinc/blackbox/plugincontainer.hh>

namespace Gecode { namespace FlatZinc {

    class BlackBox: public Propagator {
        protected:
            // Array of views
            ViewArray<Int::IntView> x;
            /// Array of views
            ViewArray<Int::IntView> y;
            Gecode::FlatZinc::PluginContainer* bbFunctionContainer;
            /// Constructor for cloning \a p
            BlackBox(Space& home, BlackBox& p);
            // /// Constructor for rewriting \a p during cloning
            // BlackBox(Space& home, Propagator& p, ViewArray<Int::IntView>& x);
            /// Constructor for creation
        public:
            BlackBox(Home home, ViewArray<Int::IntView>& x0, ViewArray<Int::IntView>& y0);
            /// Cost function (defined as low linear)
            virtual PropCost cost(const Space& home, const ModEventDelta& med) const;
            /// Schedule function
            virtual void reschedule(Space& home);
            /// Delete propagator and return its size
            virtual size_t dispose(Space& home);

            virtual ExecStatus propagate(Space &home, const ModEventDelta &);

            virtual Propagator *copy(Space &home);

            static ExecStatus post(Home home, ViewArray<Int::IntView>& x, ViewArray<Int::IntView>& y);

    };
    void blackbox(Home home, const IntVarArgs& xv, const IntVarArgs& yv);
}}
