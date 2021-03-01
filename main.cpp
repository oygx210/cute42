#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "WidgetHeaders/mainwindow_42.h"
#include "DataHeaders/qt42_headers.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   app.setApplicationName(appName);
   app.setApplicationVersion("1.0");
   app.setOrganizationName("Yu Tso (Roy); 左昀");
   QCommandLineParser parser;
   parser.setApplicationDescription(QCoreApplication::applicationName());
   parser.addHelpOption();
   parser.addVersionOption();
   parser.process(app);
   MainWindow_42 w;
   w.show();
   return app.exec();   
}
