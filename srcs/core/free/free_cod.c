// Function to free minor classes
#include "class_of_device.h"
#include <stdlib.h>

static void free_minor_classes(t_le_cod_minor_class *minor)
{
    t_le_cod_minor_class *tmp;
    while (minor)
    {
        tmp = minor;
        minor = minor->next;
        free(tmp->name);
        free(tmp);
    }
}

// Function to free subminor classes
static void free_subminor_classes(t_le_cod_subminor_class *subminor)
{
    t_le_cod_subminor_class *tmp;
    while (subminor)
    {
        tmp = subminor;
        subminor = subminor->next;
        free(tmp->name);
        free(tmp);
    }
}

// Function to free minor bits
static void free_minor_bits(t_le_cod_minor_bit *minor_bit)
{
    t_le_cod_minor_bit *tmp;
    while (minor_bit)
    {
        tmp = minor_bit;
        minor_bit = minor_bit->next;
        free(tmp->name);
        free(tmp);
    }
}

// Function to free major classes
static void free_major_classes(t_le_cod_major_class *major)
{
    t_le_cod_major_class *tmp;
    while (major)
    {
        tmp = major;
        major = major->next;
        free(tmp->name);
        free_minor_classes(tmp->minor);
        free_subminor_classes(tmp->subminor);
        free_minor_bits(tmp->minor_bits);
        free(tmp);
    }
}

// Function to free services
static void free_services(t_le_cod_service *service)
{
    t_le_cod_service *tmp;
    while (service)
    {
        tmp = service;
        service = service->next;
        free(tmp->name);
        free(tmp);
    }
}

// Function to free the Class of Device (CoD)
void free_class_of_device_list(t_le_class_of_device *cod)
{
    if (cod)
    {
        free_major_classes(cod->major_class);
        free_services(cod->service);
    }
}
