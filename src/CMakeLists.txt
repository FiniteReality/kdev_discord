set(kdev_discord_SRCS
    kdev_discord.cpp
)

ecm_qt_declare_logging_category(kdev_discord_SRCS
    HEADER debug.h
    IDENTIFIER PLUGIN_KDEV_DISCORD
    CATEGORY_NAME "kdevelop.plugin.kdev_discord"
)

kdevplatform_add_plugin(kdev_discord
    JSON kdev_discord.json
    SOURCES ${kdev_discord_SRCS}
)
add_dependencies(kdev_discord discord-rpc)

target_link_libraries(kdev_discord
    KF5::TextEditor
    KDev::Interfaces
    discord-rpc
)
