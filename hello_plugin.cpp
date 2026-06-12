#include <vultra/core/engine/engine_context.hpp>
#include <vultra/core/plugin/engine_plugin.hpp>
#include <vultra/function/services/script_service.hpp>

#include <lua.hpp>

#if defined(_WIN32)
#define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace
{
    int helloFromCpp(lua_State* L)
    {
        const char* name = luaL_optstring(L, 1, "world");
        lua_pushfstring(L, "Hello, %s, from native C++!", name ? name : "world");
        return 1;
    }

    class HelloPlugin final : public vultra::EnginePlugin
    {
    public:
        const char* name() const override { return "Vultra Hello Plugin"; }

        bool install(vultra::EngineContext& ctx) override
        {
            auto* scripts = ctx.services.tryGet<vultra::IScriptService>();
            if (!scripts)
                return false;

            lua_State* L = scripts->luaState();
            lua_pushcfunction(L, helloFromCpp);
            lua_setglobal(L, "helloFromCpp");
            return true;
        }

        void uninstall(vultra::EngineContext& ctx) override
        {
            auto* scripts = ctx.services.tryGet<vultra::IScriptService>();
            if (!scripts)
                return;

            lua_State* L = scripts->luaState();
            lua_pushnil(L);
            lua_setglobal(L, "helloFromCpp");
        }
    };
} // namespace

PLUGIN_EXPORT vultra::EnginePlugin* vultraCreatePlugin()
{
    return new HelloPlugin();
}

PLUGIN_EXPORT void vultraDestroyPlugin(vultra::EnginePlugin* plugin)
{
    delete plugin;
}
