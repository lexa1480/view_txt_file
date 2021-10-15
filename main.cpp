#include "mainwindow.h"
#include "CommandLineArgs.h"

#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QTextStream>


int main(int argc, char *argv[])
{
    boost::program_options::variables_map vm;
    if( CheckCommandLineArgs( argc, argv, vm ) )
    {
        if( vm.count(c_szArgPathFile) )
        {
            QFile file( (vm[c_szArgPathFile].as<std::string>()).c_str() );
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream qtsInFile(&file);
                if(vm.count(c_szArgTypeCoding))
                {
                    qtsInFile.setCodec((vm[c_szArgTypeCoding].as<std::string>()).c_str());
                }
                QString qsResText = qtsInFile.readAll();

                QApplication a(argc, argv);
                MainWindow w;
                if(vm.count(c_szArgTitle))
                {
                    w.setWindowTitle((vm[c_szArgTitle].as<std::string>()).c_str());
                }
                else
                {
                    std::string sTitle = file.fileName().toStdString();
                    sTitle = sTitle.substr(sTitle.find_last_of("\\/") + 1,std::string::npos);
                    w.setWindowTitle(sTitle.c_str());
                }
                w.SetText( qsResText );
                w.show();
                return a.exec();
            }
            else
            {
                std::cout << Cons( "Error open file" ) << std::endl;
                return 1;
            }
        }
    }

    return 0;
}
