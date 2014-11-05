#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QProcess>

class QSettings;

// This class will be responsible for management of application udpate process
class UpdateController : public QObject
{
    Q_OBJECT
public:

    // Enum which define of type of action, i.e. which type of process is execute
    enum eTypeAction {
        eCheckUpdate,
        eInstall,
        eNone
    };

    // Enum which define of type of update
    enum eTypeUpdate {
        eUpToDate = 0,
        eLow,
        eMedium,
        eHigh,
        eCritical
    };

    // Enum which define of type of version in VersionLog file
    enum eTypeVersion {
        ePast = 0,
        eCurrent,
        eNew
    };

    UpdateController();
    virtual ~UpdateController();

    // Method used for getting and parsing of version log
    void getVersions(QMap<QString, QMap<QString, QString> > &feauture, QStringList &listGroup);

   // Method used to return type of version
   eTypeVersion getTypeVersion(const QString& version);

   // Method used to start upgrade
   void makeUpgrate();

private slots:
    // Slot is called when need to check for updates
    void checkUpdate();

    // Slot is call when process is finished
    void onProcessFinish(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    // Signal is emit when process for update is finished and will be catch in GUI
    void updateVersion(int checkVersion);
    // Signal is emit when process for install is finished and will be catch in GUI
    void installFinish();
private:
    // Method will be responsible for getting of period for checking of udpated
    // from configuration file, it is WorldcoinBC.cfg, and this period will be in hours
    double getPeriodFromConfig();

    // Method used for run the process
    void runProcess(const QStringList &arguments);

    // Method used to process standard output from execution of update app
    void processOutput(const QByteArray& execOutput);

    // Method used for parse version that is received from server
    void parseVersion(const QString& receivedVersion);

    // Method used for checking of the version (example "1.0.2|Crypto Punisher|4|2")
    eTypeUpdate checkVersion(const QString& inVersion);

    // Method used for compare versions
    // In case when return 0 means first version is fresher, -1 means are equal, and 1 means that second is fresher
    int compareVersions(char* firstVer, char* secondVer);

    // Method used for get current app version
    QString getCurrentVersion();

    // Method used for processing of install (call when install process is finished)
    void processInstall(const QString& receivedInstallResult);

    // Used for manipulation with settings from config
    QSettings *m_settingsConfig;

    // Used for manipulation with settings version log file
    QSettings *m_settingsVersion;

    // Used for checking of updaptes
    QTimer m_timer;

    // Used for starting of update app
    QProcess* m_process;

    // Used to defined current action
    eTypeAction m_action;
};
#endif // UPDATECONTROLLER_H

