#ifndef LIBS_SCOPE_GUARD_WT_SCOPE_GUARD_HPP
#define LIBS_SCOPE_GUARD_WT_SCOPE_GUARD_HPP

#include <functional>

namespace wt {
    class ScopeGuard {
    public:
        explicit ScopeGuard(std::function<void()>);
        ~ScopeGuard();

        ScopeGuard(const ScopeGuard&) = delete;
        ScopeGuard(ScopeGuard&&) = delete;

        ScopeGuard& operator=(const ScopeGuard&) = delete;
        ScopeGuard& operator=(ScopeGuard&&) = delete;

    private:
        std::function<void()> f;
    };
}

#endif
