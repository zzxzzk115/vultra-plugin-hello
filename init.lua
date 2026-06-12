-- "hello" example plugin (native C++ + Lua).
--
-- The PluginSystem runs this file and, on the returned table, calls on_install() at load and
-- on_uninstall() at shutdown. The native side registers helloFromCpp() into the shared Lua state;
-- this Lua entry calls it and also registers a pure-Lua helper for scripts to call.
local M = {}

function M.on_install()
    print("[hello-plugin] installed")

    function helloFromLua(who)
        return "Hello, " .. tostring(who or "world") .. ", from Lua!"
    end

    if type(helloFromCpp) == "function" then
        print("[hello-plugin] " .. tostring(helloFromCpp("Vultra")))
    else
        print("[hello-plugin] native helloFromCpp() binding is unavailable")
    end

    print("[hello-plugin] " .. tostring(helloFromLua("Vultra")))
end

function M.on_uninstall()
    print("[hello-plugin] uninstalled")
    helloFromLua = nil
end

return M
