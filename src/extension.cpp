#include <algorithm>
#include <vector>
#include <string>
#include <functional>

#include "idasdk.h"

static void c_import_module(const char* module, const char* windir, uval_t modnode, const char* ostype)
{
    import_module(module, windir, modnode, nullptr, ostype);
}

namespace py = pybind11;
static std::vector<std::function<void(py::object&)>> EXTENSION_TABLE =
{
    [](auto& obj) 
    { 
        obj.attr("import_module") = py::cpp_function(&c_import_module);
    },
};

void register_extensions()
{
    // Acquire the GIL before working with Python.
    py::gil_scoped_acquire acquire;
    py::module_ idaapi_module = py::module_::import(PY_MODULE_NAME);

    // Check if 'ext' exists in idaapi
    py::object ext;
    if (py::hasattr(idaapi_module, PY_EXT_NAME))
    {
        ext = idaapi_module.attr(PY_EXT_NAME);
    }
    else
    {
        // Use idaapi's special object_t class to create a new object
        ext = py::eval("idaapi.object_t()");
        idaapi_module.add_object(PY_EXT_NAME, ext);
    }

    // Alternatively, to import the builtins module (global scope), just pass in "builtins"
    py::module_ builtins = py::module_::import("builtins");

    // Bind all extensions
    for (auto& binding : EXTENSION_TABLE)
        binding(ext);
}
//! EXTENSIONS END
