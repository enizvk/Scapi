#include "appwindow.h"
#include <QAction>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QCoreApplication>
#include <QCloseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>


AppWindow::AppWindow():server_(new SiServer(this))
{
    createUI();
    createActions();

    resize(300,300);

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    //Start server
    server_ = new SiServer(this,ipAddress,55056);
    connect(server_,SIGNAL(serverStatusChanged(ServerStatus)),this,SLOT(onServerStatusChange(ServerStatus)));
    connect(server_,SIGNAL(serverLogChanged(QString)),this,SLOT(onServerMessageChange(QString)));

    if(!server_->tryConnect())
    {
        infoLabel_->setText(tr("Server could not be started!"));
    }

    ipAddrLineEdit_->setText(ipAddress);
    portLineEdit_->setText(QString::number(server_->getPort()));


}

void AppWindow::onServerStatusChange(Scapi::Server::Status status)
{
    QString m = "Server is listening...";
    if(status != SiServer::Listening)
    {
        m = "Server is not listening...";
    }

    this->setToolTip(m);
    infoLabel_->setText(m);
    logListWidget_->addItem(m);
}

void AppWindow::onServerMessageChange(QString msg)
{
    logListWidget_->addItem(msg);
}

void AppWindow::setVisible(bool visible)
{
    //restoreAction_->setEnabled(!visible);
    QDialog::setVisible(visible);
}

void AppWindow::createActions()
{

//    quitAction_ = new QAction(tr("&Quit"), this);
//    connect(quitAction_, &QAction::triggered, qApp, &QCoreApplication::quit);

//    prgAboutAction_ = new QAction(tr("&About"),this);
//    connect (prgAboutAction_,&QAction::triggered,this,&AppWindow::showAboutMessage);

//    startStopAction_ = new QAction(tr("&Start"),this);
////    connect(startStopAction_,&QAction::toggled,this,&AppWindow::startStopServer);

}


void AppWindow::createUI()
{
    QGridLayout* mainLayout = new QGridLayout(this);

    infoLabel_ = new QLabel(this);
    infoLabel_->setText("");

    portLineEdit_ = new QLineEdit(this);
    portLineEdit_->setValidator(new QIntValidator(0,99999,this));

    ipAddrLineEdit_ = new QLineEdit(this);
    ipAddrLineEdit_->setEnabled(false);

    logListWidget_ = new QListWidget(this);
    logListWidget_->setAutoScroll(true);
    logListWidget_->setAlternatingRowColors(true);
    mainLayout->setColumnStretch(3,3);

    mainLayout->addWidget(new QLabel(tr("Port:")),1,0,1,1,Qt::AlignRight);
    mainLayout->addWidget(portLineEdit_,1,1,1,1,Qt::AlignLeft);
    mainLayout->addWidget(new QLabel(tr("Server address:")),2,0,1,1,Qt::AlignRight);
    mainLayout->addWidget(ipAddrLineEdit_,2,1,1,1,Qt::AlignLeft);
    mainLayout->addWidget(new QLabel(tr("Server log:")),3,0,1,2,Qt::AlignLeft);
    mainLayout->addWidget(logListWidget_,4,0,1,3,Qt::AlignAbsolute);
    mainLayout->addWidget(infoLabel_,5,0,1,3,Qt::AlignBaseline);

}

void AppWindow::closeEvent(QCloseEvent *event)
{
 //program close
}
#endif

