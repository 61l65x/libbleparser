#ifndef CLASS_OF_DEVICE_H
# define CLASS_OF_DEVICE_H

# ifdef __cplusplus
extern "C"
{
# endif

# include <stdint.h>

	typedef struct s_le_cod_minor_class
	{
		uint32_t						value;
		char							*name;
		struct s_le_cod_minor_class		*next;
	} t_le_cod_minor_class;

	typedef struct s_le_cod_subminor_class
	{
		uint32_t						value;
		char							*name;
		struct s_le_cod_subminor_class	*next;
	} t_le_cod_subminor_class;

	typedef struct s_le_cod_minor_bit
	{
		uint32_t						value;
		char							*name;
		struct s_le_cod_minor_bit		*next;
	} t_le_cod_minor_bit;

	typedef struct s_le_cod_major_class
	{
		uint32_t						major;
		char							*name;
		uint32_t						subsplit;
		t_le_cod_minor_class			*minor;
		t_le_cod_subminor_class			*subminor;
		t_le_cod_minor_bit				*minor_bits;
		struct s_le_cod_major_class		*next;
	} t_le_cod_major_class;

	typedef struct s_le_cod_service
	{
		uint32_t						bit;
		char							*name;
		struct s_le_cod_service			*next;
	} t_le_cod_service;

	typedef struct s_le_class_of_device
	{
		t_le_cod_major_class			*major_class;
		t_le_cod_service				*service;
	} t_le_class_of_device;

# ifdef __cplusplus
}
# endif

#endif