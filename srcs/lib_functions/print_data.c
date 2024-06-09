#include "assigned_numbers.h"
#include "ble_parser.h"
# include <stdint.h>

t_le_manufacturer_data *get_manufacturer_data(t_le_adv_data_repository *repo, int manufacturer_id);
t_le_cod_major_class *get_cod_major_class(t_le_adv_data_repository *repo, uint8_t class_code);
t_le_cod_minor_class *get_cod_minor_class(t_le_cod_major_class *major_class, uint8_t class_code);
t_le_cod_subminor_class *get_cod_subminor_class(t_le_cod_major_class *major_class, uint8_t class_code);
t_le_cod_minor_bit *get_cod_minor_bit(t_le_cod_major_class *major_class, uint8_t class_code);
t_le_cod_service *get_cod_service(t_le_adv_data_repository *repo, uint32_t bit);

void print_all_ad_types(t_ble_parser *parser, uint8_t *data, size_t len)
{
    const t_le_ad_types *ad_type = parser->repo.ad_types;
    size_t i = 0;

    while(i < len)
    {
        uint8_t field_len = data[i];
        if (field_len == 0 || i + field_len >= len)
            break;
        uint8_t field_type = data[i + 1];
        while (ad_type)
        {
            if (ad_type->type == field_type)
            {
                printf("AD Type: %s\n", ad_type->name);
                break;
            }
            ad_type = ad_type->next;
        }
        i += field_len + 1;
    }

}

void print_adv_data_readable(t_ble_parser *parser, uint8_t *data, size_t len)
{
    size_t index = 0;
    uint8_t field_len;
    uint8_t field_type;
    int manufacturer_id;
    t_le_adv_data_repository *repo = &parser->repo;

    printf("Advertising Data: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");

    print_all_ad_types(parser, data, len);
    while (index < len) {
        field_len = data[index];
        if (field_len == 0 || index + field_len >= len) {
            break;
        }
        field_type = data[index + 1];

        switch (field_type) {
            case AD_TYPE_MANUFACTURER_SPECIFIC_DATA: // Manufacturer Specific Data
                if (field_len >= 3) {
                    manufacturer_id = data[index + 2] | (data[index + 3] << 8);
                    printf("Manufacturer ID: %04x\n", manufacturer_id);
                    t_le_manufacturer_data *manufacturer = get_manufacturer_data(repo, manufacturer_id);
                    printf("Manufacturer Name: %s\n", manufacturer ? manufacturer->name : "Unknown");
                }
                break;
            case AD_TYPE_CLASS_OF_DEVICE: // Class of Device
                if (field_len >= 4) {
                    uint32_t class_of_device = (data[index + 2] << 16) | (data[index + 3] << 8) | data[index + 4];
                    printf("Class of Device: 0x%06x\n", class_of_device);

                    uint8_t major_class_code = (class_of_device >> 8) & 0x1F;  // Extracting major class code
                    uint8_t minor_class_code = (class_of_device >> 2) & 0x3F; // Extracting minor class code
                    uint32_t service_bits = class_of_device >> 13;             // Extracting service bits

                    t_le_cod_major_class *major_class = get_cod_major_class(repo, major_class_code);
                    if (major_class) {
                        printf("Major Class: %s\n", major_class->name);
                        t_le_cod_minor_class *minor_class = get_cod_minor_class(major_class, minor_class_code);
                        if (minor_class) {
                            printf("Minor Class: %s\n", minor_class->name);
                        } else {
                            printf("Unknown Minor Class\n");
                        }
                        t_le_cod_subminor_class *subminor_class = get_cod_subminor_class(major_class, minor_class_code);
                        if (subminor_class) {
                            printf("Subminor Class: %s\n", subminor_class->name);
                        } else {
                            printf("Unknown Subminor Class\n");
                        }
                        t_le_cod_minor_bit *minor_bit = get_cod_minor_bit(major_class, minor_class_code);
                        if (minor_bit) {
                            printf("Minor Bit: %s\n", minor_bit->name);
                        } else {
                            printf("Unknown Minor Bit\n");
                        }
                    } else {
                        printf("Unknown Major Class\n");
                    }

                    t_le_cod_service *service = get_cod_service(repo, service_bits);
                    if (service) {
                        printf("Service: %s\n", service->name);
                    } else {
                        printf("Unknown Service\n");
                    }
                } else {
                    printf("Invalid Class of Device field length: %d\n", field_len);
                }
                break;
            default:
                printf("Unhandled field type: 0x%02x\n", field_type);
                break;
        }
        index += field_len + 1;
    }
    printf("\n");
}
