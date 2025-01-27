// BLEParser.h

#ifndef BLE_PARSER_H
#define BLE_PARSER_H

#include "./parse_yaml/data_structs.h"
#include <linux/limits.h>
#include <string>

# define LIB_NOT_FOUND \
	"Could not find libbleparser directory \
if you have changed the name of the library file please change it back to the original 'libbleparser' \n"

# define LE_REPO_AD_TYPES_PATH "srcs/repository/assigned_numbers/core/ad_types.yaml"
# define LE_REPO_COMPANY_IDENTIFIERS_PATH "srcs/repository/assigned_numbers/company_identifiers/company_identifiers.yaml"
# define LE_REPO_COD_PATH "srcs/repository/assigned_numbers/core/class_of_device.yaml"


typedef struct s_yaml_paths
{
	char						ad_types_path[PATH_MAX];
	char						company_identifiers_path[PATH_MAX];
	char						cod_path[PATH_MAX];
}								t_yaml_paths;

struct ParsedAdvData {
    t_ClassOfDeviceData cod_data;
    t_ManufacturerData manf_data;
    
    ParsedAdvData() = default;

    void printData() const {
    }
};


void							print_class_of_device(t_le_class_of_device *cod);
void							print_manufacturer_tree(t_le_manufacturer_data *node);

typedef struct s_le_adv_data_repository
{
	t_le_ad_types				*ad_types;
	t_le_implemented_ad_types	implemented_ad_types;
	int							num_le_adv_data;
}								t_le_adv_data_repository;

class BLEParser {
public:
    // Constructor and Destructor
    BLEParser();
    ~BLEParser();

    // Public methods for the user
    bool loadYAMLData(const std::string& yaml_file);
    ParsedAdvData &parseAdvData(const uint8_t* data, size_t len) const;
    
    void printClassOfDevice() const;
    void printManufacturerData() const;
    
    // Example method to fetch manufacturer data
    std::string getManufacturerName(int manufacturer_id) const;

private:
    // Encapsulated repository data
    t_le_adv_data_repository repo;

    // Helper methods to interact with the repository
    void loadManufacturerData(const std::string& file_path);
    void loadClassOfDeviceData(const std::string& file_path);
};

#endif // BLE_PARSER_H
