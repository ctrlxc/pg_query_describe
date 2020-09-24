#include <fstream>

namespace d
{
    #include "describe.h"
}

class App
{
public:
    enum ArgPos {
        host = 1,
        port,
        db,
        user,
        pass,
        query,
    };

    int main(int argc, const char* argv[]) {

        std::ifstream ifs(argv[ArgPos::query]);
        std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        d::Config config = {
            argv[ArgPos::host],
            argv[ArgPos::port],
            argv[ArgPos::db],
            argv[ArgPos::user],
            argv[ArgPos::pass],
            str.c_str(),
        };

        return d::describe(&config);
    }
};

int main(int argc, const char* argv[])
{
    App app;

    return app.main(argc, argv);
}
