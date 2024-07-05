#include "ble_parser.h"

t_le_cod_major_class	*get_cod_major_class(t_le_adv_data_repository *repo,
							uint8_t class_code);
t_le_cod_minor_class	*get_cod_minor_class(t_le_cod_major_class *major_class,
							uint8_t class_code);
t_le_cod_subminor_class	*get_cod_subminor_class(t_le_cod_major_class *major_class,
							uint8_t class_code);
t_le_cod_minor_bit		*get_cod_minor_bit(t_le_cod_major_class *major_class,
							uint8_t class_code);
t_le_cod_service		*get_cod_service(t_le_adv_data_repository *repo,
							uint32_t bit);

void	fill_class_of_device_data(t_ClassOfDeviceData *cod_data,
		t_le_adv_data_repository *repo, uint8_t major_class_code,
		uint8_t minor_class_code, uint8_t subminor_class_code,
		uint8_t minor_bit_code, uint32_t service_bits)
{
	t_le_cod_major_class	*major_class;
	t_le_cod_minor_class	*minor_class;
	t_le_cod_subminor_class	*subminor_class;
	t_le_cod_minor_bit		*minor_bit;
	t_le_cod_service		*service;

	if (!cod_data || !repo)
	{
		fprintf(stderr, "Invalid input parameters\n");
		return ;
	}
	// Get major class
	major_class = get_cod_major_class(repo, major_class_code);
	if (major_class)
	{
		strncpy(cod_data->major_class_name, major_class->name,
			sizeof(cod_data->major_class_name) - 1);
		cod_data->major_class_name[sizeof(cod_data->major_class_name)
			- 1] = '\0';
		// Get minor class
		minor_class = get_cod_minor_class(major_class, minor_class_code);
		if (minor_class)
		{
			strncpy(cod_data->minor_class_name, minor_class->name,
				sizeof(cod_data->minor_class_name) - 1);
			cod_data->minor_class_name[sizeof(cod_data->minor_class_name)
				- 1] = '\0';
			// Get subminor class
			subminor_class = get_cod_subminor_class(major_class,
					subminor_class_code);
			if (subminor_class)
			{
				strncpy(cod_data->subminor_class_name, subminor_class->name,
					sizeof(cod_data->subminor_class_name) - 1);
				cod_data->subminor_class_name[sizeof(cod_data->subminor_class_name)
					- 1] = '\0';
				// Get minor bit
				minor_bit = get_cod_minor_bit(major_class, minor_bit_code);
				if (minor_bit)
				{
					strncpy(cod_data->minor_bit_name, minor_bit->name,
						sizeof(cod_data->minor_bit_name) - 1);
					cod_data->minor_bit_name[sizeof(cod_data->minor_bit_name)
						- 1] = '\0';
				}
				else
				{
					strncpy(cod_data->minor_bit_name, "Unknown Minor Bit",
						sizeof(cod_data->minor_bit_name) - 1);
					cod_data->minor_bit_name[sizeof(cod_data->minor_bit_name)
						- 1] = '\0';
				}
				// Get service
				service = get_cod_service(repo, service_bits);
				if (service)
				{
					strncpy(cod_data->service_name, service->name,
						sizeof(cod_data->service_name) - 1);
					cod_data->service_name[sizeof(cod_data->service_name)
						- 1] = '\0';
				}
				else
				{
					strncpy(cod_data->service_name, "Unknown Service",
						sizeof(cod_data->service_name) - 1);
					cod_data->service_name[sizeof(cod_data->service_name)
						- 1] = '\0';
				}
			}
			else
			{
				strncpy(cod_data->subminor_class_name, "Unknown Subminor Class",
					sizeof(cod_data->subminor_class_name) - 1);
				cod_data->subminor_class_name[sizeof(cod_data->subminor_class_name)
					- 1] = '\0';
			}
		}
		else
		{
			strncpy(cod_data->minor_class_name, "Unknown Minor Class",
				sizeof(cod_data->minor_class_name) - 1);
			cod_data->minor_class_name[sizeof(cod_data->minor_class_name)
				- 1] = '\0';
		}
	}
	else
	{
		strncpy(cod_data->major_class_name, "Unknown Major Class",
			sizeof(cod_data->major_class_name) - 1);
		cod_data->major_class_name[sizeof(cod_data->major_class_name)
			- 1] = '\0';
	}
	cod_data->class_of_device = (major_class_code << 8) | (minor_class_code << 2) | (subminor_class_code >> 2);
}
