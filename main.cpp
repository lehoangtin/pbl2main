#include "UIManager.h"
#include <iostream>

int main()
{
    try
    {
        UIManager ui;
        ui.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Lỗi: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}