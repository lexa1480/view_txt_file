#include "mainwindow.h"
#include "CommandLineArgs.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

int main(int argc, char *argv[])
{ 
    boost::program_options::variables_map vm;
    if( CheckCommandLineArgs( argc, argv, vm ) )
    {
        if( vm.count(c_szArgPathFile) )
        {
            QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP-1251"));
            QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP-1251"));
            QFile file( ((vm[c_szArgPathFile].as<std::string>()).c_str()) );
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QApplication a(argc, argv);
                MainWindow w;

                QTextStream qtsInFile(&file);
                if(vm.count(c_szArgTypeCoding))
                {
                    qtsInFile.setCodec((vm[c_szArgTypeCoding].as<std::string>()).c_str());
                }
                QString qsResText = qtsInFile.readAll();
                w.SetText( qsResText );

                QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
                if(vm.count(c_szArgTitle))
                {
                    w.setWindowTitle((vm[c_szArgTitle].as<std::string>()).c_str());
                }
                else
                {
                    std::string sTitle = vm[c_szArgPathFile].as<std::string>();
                    sTitle = sTitle.substr(sTitle.find_last_of("\\/") + 1,std::string::npos);
                    w.setWindowTitle( sTitle.c_str() );
                }

                if(vm.count(c_szArgNoMove))
                {
                    w.setWindowFlags(Qt::CustomizeWindowHint);
                }

                w.show();
                if(vm.count(c_szArgNoResize))
                {
                    w.setFixedSize(w.size());
                }


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
