/*
** EPITECH PROJECT, 2018
** Resource
** File description:
** Implementation of Resource
*/

#include "Resource.hpp"

Resource::Resource(const Type &type, unsigned int quantity)
	: type(type), quantity(quantity)
{}

Resource::Type Resource::getType() const
{
	return type;
}

unsigned int Resource::getQuantity() const
{
	return quantity;
}

void Resource::setQuantity(unsigned int quantity)
{
	Resource::quantity = quantity;
}
