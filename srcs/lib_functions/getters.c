// Function to get manufacturer data by ID
#include "ble_parser.h"
#include "data_structs.h"

t_le_manufacturer_data *get_manufacturer_data(t_le_adv_data_repository *repo, int manufacturer_id)
{
    t_le_manufacturer_data *current = repo->implemented_ad_types.root;

    while (current) {
        if (current->id == manufacturer_id) {
            return current;
        } else if (manufacturer_id < current->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

t_le_cod_major_class *get_cod_major_class(t_le_adv_data_repository *repo, uint8_t class_code)
{
    t_le_cod_major_class *current = repo->implemented_ad_types.cod.major_class;

    while (current) {
        if (current->major == class_code) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

t_le_cod_minor_class *get_cod_minor_class(t_le_cod_major_class *major_class, uint8_t class_code)
{
    t_le_cod_minor_class *current = major_class->minor;

    while (current) {
        if (current->value == class_code) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

t_le_cod_subminor_class *get_cod_subminor_class(t_le_cod_major_class *major_class, uint8_t class_code)
{
    t_le_cod_subminor_class *current = major_class->subminor;

    while (current) {
        if (current->value == class_code) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}


t_le_cod_minor_bit *get_cod_minor_bit(t_le_cod_major_class *major_class, uint8_t class_code)
{
    t_le_cod_minor_bit *current = major_class->minor_bits;

    while (current) {
        if (current->value == class_code) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

t_le_cod_service *get_cod_service(t_le_adv_data_repository *repo, uint32_t bit)
{
    t_le_cod_service *current = repo->implemented_ad_types.cod.service;

    while (current) {
        if (current->bit == bit) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}