#include "idasdk.h"
#include "extension.h"

class python_ext_plg_t : public plugmod_t, public event_listener_t
{
public:
    python_ext_plg_t() 
    {
        hook_event_listener(HT_UI, this);
    }

    ssize_t idaapi on_event(ssize_t code, va_list va) override
    {
        if (code == ui_initing_database)
        {
#ifdef __NT__
            LoadLibraryA("python_ext" PLG_SUFFIX);
#else
            dlopen("python_ext" PLG_SUFFIX, RTLD_NOLOAD | RTLD_LAZY);
#endif
            register_extensions();
            remove_event_listener(this);
        }
        return 0;
    }

    bool idaapi run(size_t) override 
    { 
        return true; 
    }

    ~python_ext_plg_t() override 
    {
        unhook_event_listener(HT_UI, this);
    }
};

//--------------------------------------------------------------------------
plugin_t PLUGIN = 
{
    IDP_INTERFACE_VERSION,
    PLUGIN_MULTI | PLUGIN_FIX /* | PLUGIN_HIDE*/,// Plugin flags
    []()->plugmod_t* { return new python_ext_plg_t(); },
    nullptr,                   // Terminate function
    nullptr,                   // Run function
    "Python extension plugin for PS4 module loader", // Long comment about the plugin
    "",                       // Multiline help about the plugin
    "ps4_helper",             // The preferred short name of the plugin
    "Ctrl-4"                  // The preferred hotkey to run the plugin
};
