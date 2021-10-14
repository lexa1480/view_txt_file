#include "mainwindow.h"
#include "CommandLineArgs.h"

#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    boost::program_options::variables_map vm;
    if(CheckCommandLineArgs( argc, argv, vm ))
    {
        QFile file( (vm[c_szArgPathFile].as<std::string>()).c_str() );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << Cons( "Error open file" ) << std::endl;
            return 1;
        }

        QTextStream qtsInFile(&file);
        if(vm.size() == 2)
        {
            qtsInFile.setCodec((vm[c_szArgTypeCoding].as<std::string>()).c_str());
        }
        else
        {
            std::cout << Cons( "No file encoding" ) << std::endl;
        }

        QString qsRes = qtsInFile.readAll();

        w.SetText( qsRes );
        w.show();
    }

    return a.exec();
}
