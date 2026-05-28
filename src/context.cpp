#include "math_core.h"
#include <cstring>
#include <cstdlib>

// Internal state — empty for now, we'll fill this in later
struct MathContext {
    int placeholder;
};

MathContext* mc_create_context() {
    return new MathContext{};
}

void mc_destroy_context(MathContext* ctx) {
    delete ctx;
}

static char* duplicate_string(const char* s) {
    if (!s) return nullptr;
    size_t len = std::strlen(s) + 1;
    char* dup = static_cast<char*>(std::malloc(len));
    if (dup) {
        std::strcpy(dup, s);
    }
    return dup;
}

int mc_evaluate_latex(MathContext*, const char*, char** out_result, char** out_error) {
    *out_result = duplicate_string("TODO");
    *out_error  = nullptr;
    return 0;
}

int mc_simplify_latex(MathContext*, const char*, char** out_result, char** out_error) {
    *out_result = duplicate_string("TODO");
    *out_error  = nullptr;
    return 0;
}

int mc_differentiate(MathContext*, const char*, const char*, char** out_result, char** out_error) {
    *out_result = duplicate_string("TODO");
    *out_error  = nullptr;
    return 0;
}

int mc_solve_latex(MathContext*, const char*, const char*, char** out_result, char** out_error) {
    *out_result = duplicate_string("TODO");
    *out_error  = nullptr;
    return 0;
}

void mc_free_string(char* str) {
    free(str);
}

void mc_get_version(int* major, int* minor, int* patch) {
    if (major) *major = 1;
    if (minor) *minor = 0;
    if (patch) *patch = 0;
}