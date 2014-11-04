#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

#include "updatecontroller.h"

namespace Ui {
    class UpdatePage;
}

/** Dialog for update of worldcoin */
class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

    // Method is used for set of model for the update page
    void setModel(UpdateController *model);
private slots:
    // Slot is call when user click on upgrade button
    void onUpgradeButton();

private:
    // Method used for adding one line of title version
    void addVersion(const QString &version, UpdateController::eTypeVersion typeVersion);

    // Method used for adding one line of feature
    void addFeature(const QString &feauture);
    
    // Pointer to the UI
    Ui::UpdatePage *ui;

    // Used as a model
    UpdateController *model;
};
#endif // UPDATEDIALOG_H

