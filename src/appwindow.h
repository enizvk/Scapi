#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "scapi/siserver.h"
#include <QDialog>
#include <QLabel>
#include <QtGlobal>

class QLineEdit;
class QComboBox;
class QAction;
class QListWidget;

class AppWindow : public QDialog
{
    Q_OBJECT

public:
    AppWindow();
    void setVisible(bool visible) Q_DECL_OVERRIDE;


protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onServerStatusChange(SiServer::Status status);
    void onServerMessageChange(QString msg);

private:

     void createActions();
     void createTrayIcon();
     void createUI();


   /*  //UI members
     QAction *prgAboutAction_;
     QAction *startStopAction_;
     */
     QLabel* infoLabel_;
     QLineEdit *portLineEdit_;
     QLineEdit *ipAddrLineEdit_;
     QListWidget  *logListWidget_;

     //Functional members
     SiServer* server_;

};

#endif // APPWINDOW_H
