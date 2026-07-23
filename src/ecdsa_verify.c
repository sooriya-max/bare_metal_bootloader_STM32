#include "ecdsa_verify.h"
#include "uECC.h"
#include "sha256.h"

uint8_t ecdsa_verify(uint8_t *firmware, uint32_t firmware_length, uint8_t *ecdsa_signature)
{

    uint8_t hash[32];       //This is to hold the has value
    SHA256_CTX ctx;         //THis is to pass the values into the sha256 API calls


    /*Writing the SHA256 API CALLS*/
    sha256_init(&ctx);
    sha256_update(&ctx, firmware, firmware_length);
    sha256_final(&ctx, hash);

    //Public key : static to keep it in FLASH and persist across function calls, 64 since it is one point on the curev with two coordinates (x,y) and {0} for now as value
    static const uint8_t public_key[64]= {0x40, 0x44, 0x2B, 0xDF, 0x03, 0x84, 0xEE, 0xAB, 0x5E, 0x8B, 0x72, 0x6D, 0x84, 0x07, 0x8C, 0x11, 0xEA, 0xCF, 0x84, 0xC8, 0x10, 0x4D, 0x8C, 0xE5, 0x2F, 0xE6, 0x9A, 0x34, 0xFC, 0xD7, 0x58, 0x24, 0x05, 0x98, 0x73, 0xA0, 0x28, 0x8D, 0x2F, 0x28, 0xB8, 0xAC, 0x0F, 0xB6, 0x0A, 0x57, 0x4D, 0x79, 0x30, 0x5F, 0x43, 0x4D, 0xD2, 0x16, 0x79, 0x89, 0x95, 0xC1, 0xAB, 0xF5, 0x9E, 0xFC, 0x66, 0xF6};

    //This is the Actual Function call to verify : uECC_secp256r1 is the P-256 which calls the function to say which curve are we using, no need to know the internals just that it calls
    uint8_t result = uECC_verify(public_key, hash, 32, ecdsa_signature, uECC_secp256r1());
    return result;
}