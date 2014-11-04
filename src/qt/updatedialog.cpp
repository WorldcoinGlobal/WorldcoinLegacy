#include "updatedialog.h"
#include "ui_updatepage.h"

#include <QMessageBox>

UpdateDialog::UpdateDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::UpdatePage)
{
    ui->setupUi(this);

    // Set text edit to be read only
    ui->textEditVersions->setReadOnly(true);

    connect(ui->upgradeButton, SIGNAL(clicked()), this, SLOT(onUpgradeButton()));
}


UpdateDialog::~UpdateDialog()
{
}

void UpdateDialog::setModel(UpdateController *model)
{
    this->model = model;

    QTextCursor cursor(ui->textEditVersions->textCursor());

    QMap<QString, QMap<QString, QString>> versions;
    QStringList groups;
    
    // Received structure from VersionLog.cfg file
    model->getVersions(versions, groups);

    for (int i = 0; i < groups.size(); ++i)
    {
        QString titleText = "";
        QMap<QString, QString> groupKeys = versions[groups.at(i)];
        titleText += groups.at(i);
        titleText += " ";

        QMap<QString, QString>::iterator j;
        for (j = groupKeys.begin(); j != groupKeys.end(); ++j)
        {
            // Find type of version
            UpdateController::eTypeVersion verType = model->getTypeVersion(groups.at(i));
            // on first position is always name of version
            if (j == groupKeys.begin())
            {
                titleText += j.value();
                addVersion(titleText, verType);
            }
            else
            {
                addFeature(j.value());
            }
        }
    }
    
    cursor.movePosition(QTextCursor::Start);
    ui->textEditVersions->setTextCursor(cursor);
}

void UpdateDialog::addVersion(const QString &version, UpdateController::eTypeVersion typeVersion)
{
    QString finalString;
    QTextCursor cursor = ui->textEditVersions->textCursor();
    QString pastTittleColor = "<font color=\"black\" size=5>";
    QString currentTittleColor = "<font color=\"#0052AE\" size=5>";
    QString newTittleColor = "<font color=\"red\" size=5>";
    QString endHtml = "</font><br>";

    // Color is depends from type of version
    switch (typeVersion)
    {
    case UpdateController::ePast:
        finalString = pastTittleColor + version + " "+"PAST";
        break;
    case UpdateController::eCurrent:
        finalString = currentTittleColor + version + " " + "CURRENT";
        break;
    case UpdateController::eNew:
        finalString = newTittleColor + version + " " + "NEW!";
        break;
    default:
        break;
    }

    finalString = finalString + endHtml;
    finalString += "\n";
    ui->textEditVersions->insertHtml(finalString);
    cursor.movePosition(QTextCursor::End);
    ui->textEditVersions->setTextCursor(cursor);
}

void UpdateDialog::addFeature(const QString &feauture)
{
    QString finalString = "";
    QTextCursor cursor = ui->textEditVersions->textCursor();
    QString verColor = "<font color=\"darkBlue\" size=4>";
    QString endHtml = "</font><br>";

    finalString = verColor + "-" + feauture;

    finalString += endHtml;
    finalString += "\n";
    ui->textEditVersions->insertHtml(finalString);
    cursor.movePosition(QTextCursor::End);
    ui->textEditVersions->setTextCursor(cursor);
}
void UpdateDialog::onUpgradeButton()
{
    // Call method from model used for upgrade
    model->makeUpgrate();
}