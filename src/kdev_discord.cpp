#include "kdev_discord.h"

#include <debug.h>

#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(kdev_discordFactory, "kdev_discord.json", registerPlugin<kdev_discord>(); )

kdev_discord::kdev_discord(QObject *parent, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("kdev_discord"), parent)
{
    Q_UNUSED(args);

    qCDebug(PLUGIN_KDEV_DISCORD) << "Hello world, my plugin is loaded!";
}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "kdev_discord.moc"
