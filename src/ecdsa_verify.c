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
    static const uint8_t public_key[64]= {0};

    //This is the Actual Function call to verify : uECC_secp256r1 is the P-256 which calls the function to say which curve are we using, no need to know the internals just that it calls
    uint8_t result = uECC_verify(public_key, hash, 32, ecdsa_signature, uECC_secp256r1());
    return result;
}