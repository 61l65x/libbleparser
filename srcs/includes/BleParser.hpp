#ifndef BLEPARSER_HPP
# define BLEPARSER_HPP

# ifdef __cplusplus

# include "ble_parser.h"
# include <stdexcept>
# include <string>
# include <iostream>

class BleParser
{

private:
    t_ble_parser* parser;

public:

    BleParser()
    {
        parser = init_ble_parser();
        if (!parser)
            throw std::runtime_error("Failed to initialize BLE parser");
    }

    ~BleParser()
    {
        if (parser)
            destroy_ble_parser(parser);
    }

    void parseYaml()
    {
        if (parse_all_yaml(&parser->repo) != 0)
            throw std::runtime_error("Failed to parse YAML data");
    }

    void printManufacturerTree() const
    {
        print_manufacturer_tree(parser->repo.implemented_ad_types.root);
    }

    void printClassOfDevice() const
    {
        print_class_of_device(&parser->repo.implemented_ad_types.cod);
    }

};

# endif

#endif