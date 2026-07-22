#ifndef ECDSA_VERIFY_H
#define ECDSA_VERIFY_H

#include <stdint.h>

uint8_t ecdsa_verify(uint8_t *firmware, uint32_t firmware_length, uint8_t *ecdsa_signature);

#endif