#include <gecode/int.hh>

#include <gecode/flatzinc/blackbox.hh>

namespace Gecode { namespace FlatZinc {
        void
        black_box(Home home, const IntVarArgs& xv, const IntVarArgs& yv){
            // std::cout << "hi" << std::endl;
            std::out << "----------" << std::endl;

            ViewArray<Int::IntView> x(home,xv);
            ViewArray<Int::IntView> y(home,yv);

            if (home.failed())
                return;
            PostInfo pi(home);
            GECODE_ES_FAIL(Gecode::FlatZinc::BlackBox::post(home, x, y));
        }
        // The x(x0), and y(y0) construct the values
        BlackBox::BlackBox(Home home, ViewArray<Int::IntView>& x0, ViewArray<Int::IntView>& y0) : Propagator(home), x(x0), y(y0){
            // std::cout << "hi" << std::endl;
        }
        // Constructor for cloning
        // How does this bit of code work?
        BlackBox::BlackBox(Space &home, BlackBox& p) : Propagator(home, p) {
            // What does this update function do?
            x.update(home, p.x);
            y.update(home, p.y);
        }
                /// Cost function (defined as low linear)
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
            return sizeof(*this);
        };

        ExecStatus BlackBox::propagate(Space &home, const ModEventDelta &){
            // if (x.assigned()){
                // std::cout << "Assigned" << std::endl;
            // }
            return ES_NOFIX;
        };

        ExecStatus BlackBox::post(Home home, const ViewArray<Int::IntView>& x, const ViewArray<Int::IntView>& y){
            return ES_OK;
        }

        Propagator* BlackBox::copy(Space &home) {
            return new (home) BlackBox(home, *this);
        }
    }
}