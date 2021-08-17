#include <QtCore/QCoreApplication>
#include <QTimer>
#include <iostream>

#include "scapi/sidispacher.h"
#include "scapi/silogger.h"
#include "scapi/siglobals.h"

static SiLogger& logger = SiLogger::getInstance();
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(scapi);

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(kAppName);
    QCoreApplication::setApplicationVersion(kAppVer);

    SiDispacher sdisp;
    sdisp.InitCommandLine();

    QObject::connect(&sdisp,SIGNAL(finished()),&app,SLOT(quit()));

    //Delay 10ms and run the app in the event loop
    QTimer::singleShot(10,&sdisp,SLOT(run()));

    return app.exec();
}






