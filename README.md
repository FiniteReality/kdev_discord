# kdev_discord

A simple KDevelop plugin which integrates [Discord Rich Presence][discordrpc]
to allow other users to see what you're working on.

## Building ##

In theory, it should be as easy as running these shell commands:
```bash
if [ -d build ]; then mkdir build; fi
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

And then restarting KDevelop once it has successfully built. If KDevelop does
not detect the kdev_discord plugin, you may need to set your `QT_PLUGIN_PATH`
environment variable before launching KDevelop:

```bash
QT_PLUGIN_PATH=$QT_PLUGIN_PATH:$INSTALL_PREFIX/lib/plugins kdevelop
```

where `INSTALL_PREFIX` is the location where CMake is set to install the
project to.

## Screenshots ##

![Profile Popup](https://i.imgur.com/pp4XvAX.png)
![Profile Modal](https://i.imgur.com/PrJ6G1v.png)

## TO-DO ##

- Add language recognition based on MIME type
- Potentially add detection for running jobs
- Give friendly names to the plugin in the UI

[discordrpc]: https://github.com/discordapp/discord-rpc
