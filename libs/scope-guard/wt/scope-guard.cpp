#include <wt/scope-guard.hpp>

#include <unicode/ustdio.h>

namespace wt {
    ScopeGuard::ScopeGuard(std::function<void()> f) :
        f(f) {
    }

    ScopeGuard::~ScopeGuard() {
        try {
            this->f();
        } catch(...) {
            u_printf("Exception thrown from scope guard!\n");
            // don't let an exception escape the destructor
        }
    }
}
