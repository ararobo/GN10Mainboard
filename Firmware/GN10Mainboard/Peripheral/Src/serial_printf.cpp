#include "serial_printf.hpp"

template void serial_printf<>(const std::string &fmt);
template void serial_printf<unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char>(const std::string &fmt, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
template void serial_printf<unsigned char, unsigned char, unsigned char, unsigned char>(const std::string &fmt, unsigned char, unsigned char, unsigned char, unsigned char);