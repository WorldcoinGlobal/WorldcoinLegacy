#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDesktopWidget>
#include <QSettings>

#include "clientmodel.h"
#include "dialog_move_handler.h"

// Copyright year (2009-this)
// Todo: update this when changing our copyright comments in the source
const int ABOUTDIALOG_COPYRIGHT_YEAR = 2014;
const QString defWorldcoinConf = "WorldcoinBC.cfg";

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Window);
    ui->wCaption->installEventFilter(new DialogMoveHandler(this));
    // Set current copyright year
    ui->copyrightLabel->setText(tr("Copyright") + QString(" &copy; 2013-%1 ").arg("2014") + tr("Worldcoin"));

    // Center window (deleted)
//    QRect scr = QApplication::desktop()->screenGeometry();
//    move(scr.center() - rect().center());
}

void AboutDialog::setModel(ClientModel *model)
{
    if(model)
    {
       // ui->versionLabel->setText(model->formatFullVersion());
       QSettings settings(defWorldcoinConf, QSettings::IniFormat);
       settings.beginGroup("Version");
       ui->lblVersion->setText(settings.value("CurrentVersion", "1.0.0").toString());
       settings.endGroup();
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    close();
}
