/*********************************************************************************************************
 * FILENAME -     brute.h
 * 
 * DESCRIPTION -  Header file containing functions used for EVP Encryption 
 *                / Decryption as well as an error handler for both.
 *                Also included are defines for the beginning and end of the
 *                ASCII character range used within the Brute Force Search.
 *                These values can be edited to increase/decrease range of
 *                characters, based on their ASCII values.
 * 
 * NOTES -        The functions here for EVP Encryption, Decryption and the
 *                Error Handler are all provided as part of OpenSSL, within
 *                the libcrypto library.
 * 
 *                More information can be found at the following link:
 *                https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 * 
 * AUTHOR -       Jesse Batt
 * 
 * MODIFIED -     06/12/2018
 * 
 *********************************************************************************************************/

#ifndef BRUTE_H
#define BRUTE_H

/* Defines for start and end of ASCII range to be included in search */
#define ASCIISTART 33
#define ASCIIEND 122

/* Error Handler */
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

/* EVP Encryption Function */
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *truekey,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, truekey, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

/* EVP Decryption Function */
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

#endif