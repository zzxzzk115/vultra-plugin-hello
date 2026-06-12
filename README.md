# Vultra Hello Plugin

A minimal native C++ + Lua plugin for Vultra.

The native library registers one Lua binding:

```lua
helloFromCpp(name) -> string
```

The Lua entry registers one pure-Lua helper:

```lua
helloFromLua(name) -> string
```

`init.lua` calls both helpers once when the plugin is installed, so enabling the plugin
shows the native binding round trip and the pure-Lua extension path in the log.

For local development, temporarily include this repository from `libvultra/xmake.lua`, then build
the plugin target from the `libvultra` root:

```powershell
xmake build -y plugin-hello
```
