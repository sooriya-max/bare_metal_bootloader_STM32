import ecdsa

sk = ecdsa.SigningKey.generate(curve = ecdsa.NIST256p)  #To get the Signing Key AKA Private Key
vk = sk.get_verifying_key()                             #To get the Verifying Key AKA Publick Key

pem_data = sk.to_pem()                                  #To save the Private key to PEM format


# Now to open a file and write it in binary mode of our pem_data
with open("private_key.pem", "wb") as file:
    file.write(pem_data)


public_key = vk.to_string()



print("Private key saved to: tools/private_key.pem")
print("Paste this into ecdsa_verify.c:")

print("static const uint8_t public_key[64] = {")

#This gives me ["0x4A", "0x3B", "0x7F", ...]
hex_list = [f"0x{byte:02X}" for byte in public_key]

#Gives me "0x4A, 0x3B, 0x7F"
print(", ".join(hex_list))


print("};")