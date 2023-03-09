#include "App.h"

int main(int argc, char *argv[])
{
    try
    {
        App app(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
