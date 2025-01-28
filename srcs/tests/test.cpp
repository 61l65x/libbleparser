#include "BleParser.hpp"

int main()
{
    try
	{
        BleParser parser;
        parser.parseYaml();
        parser.printManufacturerTree();
        parser.printClassOfDevice();
    }
	catch (const std::exception& e)
	{
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
