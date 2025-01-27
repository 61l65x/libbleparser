#include "ble_parser.h"
#include "assigned_numbers.h"

void			fill_class_of_device_data(t_ClassOfDeviceData *cod_data,
					t_le_adv_data_repository *repo, uint8_t major_class_code,
					uint8_t minor_class_code, uint8_t subminor_class_code,
					uint8_t minor_bit_code, uint32_t service_bits);

t_ParsedAdvData	parse_adv_data(uint8_t *data, size_t len, t_ble_parser *parser)
{
	size_t		index;
	uint8_t		field_len;
	uint8_t		field_type;
	uint32_t	class_of_device;
	uint8_t		major_class_code;
	uint8_t		minor_class_code;
	uint8_t		subminor_class_code;
	uint8_t		minor_bit_code;
	uint32_t	service_bits;

	index = 0;
	t_ParsedAdvData parsed_data = {0}; // Initialize all fields to 0 or NULL
	while (index < len)
	{
		field_len = data[index];
		if (field_len == 0 || index + field_len >= len)
		{
			break ;
		}
		field_type = data[index + 1];
		switch (field_type)
		{
		case AD_TYPE_MANUFACTURER_SPECIFIC_DATA: // Manufacturer Specific Data
			if (field_len >= 3)
			{
				parsed_data.manf_data.manufacturer_id = data[index
					+ 2] | (data[index + 3] << 8);
				t_le_manufacturer_data *node = get_company_from_tree(parser->repo.implemented_ad_types.root,
                    parsed_data.manf_data.manufacturer_id);
                if (node)
                {
                    strncpy(parsed_data.manf_data.manufacturer_name, node->name, sizeof(parsed_data.manf_data.manufacturer_name) - 1);
                    // WHEN IMPLEMENTED TO FILL YAML TO STRUCT
                   // strncpy(parsed_data.manf_data.proprietary_data, node->proprietary_data, sizeof(parsed_data.manf_data.proprietary_data) - 1);
                    //parsed_data.manf_data.proprietary_data_len = node->proprietary_data_len;
                }
			}
			break ;
		case AD_TYPE_CLASS_OF_DEVICE: // Class of Device
			if (field_len >= 4)
			{
				class_of_device = (data[index + 2] << 16) | (data[index
						+ 3] << 8) | data[index + 4];
				major_class_code = (class_of_device >> 8) & 0x1F;
				minor_class_code = (class_of_device >> 2) & 0x3F;
				subminor_class_code = (class_of_device << 6) & 0xFC;
				minor_bit_code = (class_of_device >> 12) & 0x07;
				service_bits = class_of_device >> 13;
				fill_class_of_device_data(&parsed_data.cod_data,
											&parser->repo,
											major_class_code,
											minor_class_code,
											subminor_class_code,
											minor_bit_code,
											service_bits);
			}
			else
			{
				printf("Invalid Class of Device field length: %d\n", field_len);
			}
			break ;
		default:
			printf("Unhandled field type: 0x%02x\n", field_type);
			break ;
		}
		index += field_len + 1;
	}
	return (parsed_data);
}
