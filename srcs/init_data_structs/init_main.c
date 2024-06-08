#include "ble_parser.h"

int	parse_ad_types(t_le_adv_data_repository *repo);

int	init_le_ad_types(t_le_adv_data_repository *repo)
{
	t_le_ad_types	*ad_type;

	repo->ad_types = NULL;
	repo->num_le_adv_data = 0;
	(void)ad_type;
	if (parse_ad_types(repo) != 0)
	{
		return (-1);
	}
	ad_type = repo->ad_types;
	/*while (ad_type)
	{
		switch (ad_type->type)
		{
		case AD_TYPE_MANUFACTURER_SPECIFIC_DATA:
			if (parse_manufacturers(LE_COMPANY_IDENTIFIERS_PATH,
					&ad_type->implemented_ad_types->manufacturer_data) != 0)
			{
				return (-1);
			}
			break ;
		case AD_TYPE_CLASS_OF_DEVICE: // Class of Device
			if (parse_class_of_device(LE_COD_PATH,
					&ad_type->implemented_ad_types->cod) != 0)
			{
				return (-1);
			}
			break ;
		default:
			break ;
		}
		ad_type = ad_type->next;
	}*/
	return (0);
}
