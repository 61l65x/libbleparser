#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# ifdef __cplusplus
extern "C"
{
# endif

# include "class_of_device.h"
# include <stddef.h>
# include <stdint.h>

	typedef struct s_le_manufacturer_data
	{
		int								id;
		char							*name;
		char							*proprietary_data;
		size_t							proprietary_data_len;
		struct s_le_manufacturer_data	*left;
		struct s_le_manufacturer_data	*right;
	} t_le_manufacturer_data;

	typedef struct s_le_implemented_ad_types
	{
		t_le_manufacturer_data			*root;
		t_le_class_of_device			cod;
	} t_le_implemented_ad_types;

	typedef struct s_le_ad_types
	{
		uint8_t							type;
		char							*name;
		struct s_le_ad_types			*next;
	} t_le_ad_types;

	typedef struct s_ClassOfDeviceData
	{
		uint32_t						class_of_device;
		char							major_class_name[32];
		char							minor_class_name[32];
		char							subminor_class_name[32];
		char							minor_bit_name[32];
		char							service_name[32];
	} t_ClassOfDeviceData;

	typedef struct s_ManufacturerData
	{
		int								manufacturer_id;
		char							manufacturer_name[64];
		char							proprietary_data[64];
		size_t							proprietary_data_len;
	} t_ManufacturerData;

# ifdef __cplusplus
}
# endif

#endif