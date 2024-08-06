#include <iostream>
#include <args.hxx>
#include "gitutil.h"

int main(int argc, char **argv) {
    GitUtil gu;
    args::ArgumentParser parser("git utils", "© 2024 Leonhard Breuer");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::CompletionFlag completion(parser, {"complete"});
    // commands
    args::Group commands(parser, "commands");
    args::Command version(commands, "version", "generates the next version");
    // parsing
    try {
        parser.ParseCLI(argc, argv);
        if (version)
            std::cout << gu.getVersion() << std::endl;
        else
            std::cout << "No command submitted" << std::endl;
    } catch(const args::Completion& e) {
        std::cout << e.what();
        return 0;
    } catch(const args::Help&) {
        std::cout << parser << std::endl;
    } catch(const args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    } catch(const args::ValidationError& e) {
        std::cout << e.what() << std::endl;
        std::cout << parser.Help() << std::endl;
        return 1;
    }
    // GitUtil util;
    // std::cout << util.getVersion() << std::endl;
    return 0;
}
