/*********************************************************************************************************
 * FILENAME -     bruteomp.c
 * 
 * DESCRIPTION -  Source file that conducts a Brute Force Search for a 16 bit Key in order to
 *                Decrypt a Plain Text Message, parallelised using OpenMP. The program will 
 *                encrypt the message using a hard coded True Key, conduct the search and compare
 *                results against the true key. When a match is found, the program will then decrypt
 *                the encrypted message using the key solution found via the Brute Force Search.
 * 
 * NOTES -        The functions called from the header file for EVP Encryption, Decryption and the
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

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <omp.h>
#include <stdlib.h>
#include "brute.h"

#define NUM_THREADS 4

int main (void)
{
  /* Get start time of program */
  double wtime = omp_get_wtime();

  /* Hard coded 128 Bit Key and padded with # for quick testability */
  unsigned char truekey[17] = "######9Hb3######";

  /* A 128 bit Initialisation Vector */
  char iv[16] = "0123456789012345";

  /* Plain Text Message to be encrypted */
  char plaintext[17] = "Please work...";

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
     ciphertext which may be longer than the plaintext, dependant on the
     algorithm and mode */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len, worktext_len, decryptedworktext_len;

  /* Encrypt the plaintext with the True Key */
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), truekey, iv,
                            ciphertext);

  /* SANITY CHECK FOR PLAIN TEXT ENCRYPTION */
  /* printf("Ciphertext is:\n");
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len); */

  #pragma omp parallel
  {
    /* Set number of threads in program */
    omp_set_num_threads(NUM_THREADS);

    /* SANITY CHECK FOR THREAD COUNT */
    /* printf("Num of threads %d\n", omp_get_num_threads()); */

    int a,b,c,d,e,f;

    /* For Collapse cause used to convert perfectly nested loops
    into one loop, which is divided into chunks that are 
    assigned to threads. The argument is the number of loops to collapse. */
    #pragma omp parallel for collapse(4)
    for (a = ASCIISTART; a <= ASCIIEND; a++){
    for (b = ASCIISTART; b <= ASCIIEND; b++){
    for (c = ASCIISTART; c <= ASCIIEND; c++){
    for (d = ASCIISTART; d <= ASCIIEND; d++)
    {
      /* Test Key to be used in the search */
      unsigned char testkey[17] = "######xxxx######";

      /* Populate test key with characters in the search */
      testkey[6] = a;
      testkey[7] = b;
      testkey[8] = c;
      testkey[9] = d;

      /* SANITY CHECK FOR KEY TESTING */
      /* printf("Searching for key... %s\n", testkey); */

      /* If test key matches true key (solution is found...) */
      if (strcmp(testkey, truekey) == 0)
      {
        #pragma omp critical
        {   
          printf("\nKEY FOUND... %s\n\n", testkey);

          /* Decrypt the ciphertext using the key found via brute force */
          decryptedtext_len = decrypt(ciphertext, ciphertext_len, testkey, iv, decryptedtext);

          /* Add NULL terminator */
          decryptedtext[decryptedtext_len] = '\0';

          /* Output the decrypted text */
          printf("Decrypted text using generated key is:\n");
          printf("%s\n", decryptedtext);

          /* Calculate elapsed time in Wall Clock Time and output to screen */
          wtime = omp_get_wtime() - wtime;
          printf("Solution Found in %f seconds\n", wtime);

          /* Exit parallel region */
          exit(0);
        }  
      }              
    }
    }
    }
    }
  }

  return 0;
}