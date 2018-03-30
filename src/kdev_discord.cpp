#include "kdev_discord.h"

#include <debug.h>

#include <QRegularExpression>

#include <KPluginFactory>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/isession.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iproject.h>

#include <KTextEditor/Document>

#include <discord_rpc.h>

#define APPID "429055143087177730"

static bool discordReady;
static bool running;

static void SetDefaultState();

K_PLUGIN_FACTORY_WITH_JSON(kdev_discordFactory, "kdev_discord.json", registerPlugin<kdev_discord>(); )

kdev_discord::kdev_discord(QObject *parent, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("kdev_discord"), parent)
{
    Q_UNUSED(args);
    discordReady = false;

    auto* documentController = core()->documentController();

    QObject::connect(
        documentController, SIGNAL(documentActivated(KDevelop::IDocument*)),
        this, SLOT(onDocumentActivated(KDevelop::IDocument*)));

    load();
}

void kdev_discord::load()
{
    running = true;

    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));

    handlers.ready = [](){
        discordReady = true;
        SetDefaultState();
    };

    callbackThread = std::thread([]() {
        while (running)
        {
            const std::chrono::duration<int64_t, std::milli> sleepTime{500LL};
            Discord_RunCallbacks();
            std::this_thread::sleep_for(sleepTime);
        }
    });

    Discord_Initialize(APPID, &handlers, 1, nullptr);
}

void kdev_discord::unload()
{
    discordReady = false;

    Discord_Shutdown();

    running = false;
    callbackThread.join();
}

void kdev_discord::onDocumentActivated(KDevelop::IDocument* document)
{
    if (document->isTextDocument())
        setCurrentFile(document);
}

void kdev_discord::setCurrentFile(KDevelop::IDocument* document)
{
    if (discordReady)
    {
        KTextEditor::Document* textDoc = document->textDocument();
        auto fileName = textDoc->documentName();
        auto fileType = textDoc->mimeType();

        auto session = core()->activeSession();
        auto projectCtrl = core()->projectController();
        auto project = projectCtrl->findProjectForUrl(document->url());
        auto projects = session->containedProjects();

        auto sessionProjs = QString::number(projects.size());
        auto sessionName = session->name();
        auto sessionDesc = session->description();
        auto projectName = project->name();

        QString state = "Editing some code";
        QString details = fileName;

        if (!sessionName.isEmpty())
            state = "In session " + sessionName + " (" + sessionProjs + " projects)";

        if (!projectName.isEmpty())
            details = fileName + " in " + projectName;

        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));

        presence.state = state.toUtf8().constData();
        presence.details = details.toUtf8().constData();
        presence.largeImageKey = "kdev_logo";
        presence.largeImageText = sessionDesc.toUtf8().constData();
        presence.startTimestamp = time(nullptr);

        Discord_UpdatePresence(&presence);
    }
}

static void SetDefaultState()
{
    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    presence.state = "Idle";
    presence.largeImageKey = "kdev_logo";
    presence.startTimestamp = time(nullptr);

    Discord_UpdatePresence(&presence);
}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "kdev_discord.moc"
