#ifndef COMMANDLINEARGS_H
#define COMMANDLINEARGS_H

#include <boost/program_options.hpp>
#include <iostream>
#include "Cons.h"

const char c_szArgHelp[] = "help";
const char c_szArgPathFile[] = "file";
const char c_szArgTypeCoding[] = "charset";
const char c_szArgTitle[] = "title";
const char c_szArgNoResize[] = "no_resize";
const char c_szArgNoMove[] = "no_move";

inline bool CheckCommandLineArgs(int ac, char* av[], boost::program_options::variables_map& vm )
{

    namespace po = boost::program_options;
    bool bContinueExecution = false;
    try
    {
        po::options_description desc("INF> This program outputs the contents of a text file.\nAllowed options");
        desc.add_options()
                ("help,h", "Produce help message")
                ("file,f", po::value<std::string>(), "Path to file")
                ("charset,c", po::value<std::string>(), "Charset type")
                ("title,t", po::value<std::string>(), "Title window")
                ("no_move,m", "No move window")
                ("no_resize,r", "No resize window")
                ;

        po::parsed_options parsed = po::command_line_parser(ac, av).options(desc).allow_unregistered().run();
        po::store(parsed, vm);

        if( vm.count(c_szArgHelp) || ( vm.size() == 0 ) )
        {
            std::cout << desc;
        }
        else
        {
            notify(vm);
            bContinueExecution = true;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << Cons("ERR> ") << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << Cons("ERR> Exception of unknown type!") << std::endl;
    }

    return bContinueExecution;
}

#endif // COMMANDLINEARGS_H
