#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include <stddef.h>
# include <stdint.h>
# include "class_of_device.h"

// Structure for Manufacturer Specific Data
typedef struct s_le_manufacturer_data
{
	int								id;
	char							*name;
	char							*proprietary_data;
	size_t							proprietary_data_len;
	struct s_le_manufacturer_data	*left;
	struct s_le_manufacturer_data	*right;
}									t_le_manufacturer_data;

// So far Implemented profiles under ad_types.yaml
typedef struct s_le_implemented_ad_types
{
	t_le_manufacturer_data			*root;
	t_le_class_of_device			cod;
}									t_le_implemented_ad_types;

typedef struct s_le_ad_types
{
	uint8_t							type;
	char							*name;
	struct s_le_ad_types			*next;
}									t_le_ad_types;

#endif
