#ifndef KDEV_DISCORD_H
#define KDEV_DISCORD_H

#include <interfaces/iplugin.h>
#include <interfaces/idocument.h>

#include <thread>

class kdev_discord : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    // KPluginFactory-based plugin wants constructor with this signature
    kdev_discord(QObject* parent, const QVariantList& args);

    void unload() override;
public Q_SLOTS:
    void onDocumentActivated(KDevelop::IDocument* document);

private:
    std::thread callbackThread;
    void load();
    void setCurrentFile(KDevelop::IDocument* document);
};

#endif // KDEV_DISCORD_H
