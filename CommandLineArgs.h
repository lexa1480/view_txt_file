#ifndef COMMANDLINEARGS_H
#define COMMANDLINEARGS_H

#include <boost/program_options.hpp>
#include <iostream>
#include "Cons.h"

const char c_szArgHelp[] = "help";
const char c_szArgPathFile[] = "file";
const char c_szArgTypeCoding[] = "charset";

inline bool CheckCommandLineArgs(int ac, char* av[], boost::program_options::variables_map& vm )
{

    namespace po = boost::program_options;
    bool bContinueExecution = false;
    try
    {
        po::options_description desc("INF> Allowed options");
        desc.add_options()
                (c_szArgHelp, "Produce help message")
                (c_szArgPathFile, po::value<std::string>(), "Path to file")
                (c_szArgTypeCoding, po::value<std::string>(), "Charset type")
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
