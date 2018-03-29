#ifndef KDEV_DISCORD_H
#define KDEV_DISCORD_H

#include <interfaces/iplugin.h>

class kdev_discord : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    // KPluginFactory-based plugin wants constructor with this signature
    kdev_discord(QObject* parent, const QVariantList& args);
};

#endif // KDEV_DISCORD_H
