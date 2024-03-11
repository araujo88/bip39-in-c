# BIP39 Bitcoin Wallet Seed Generator

An attempt to generate 12 word seed (BIP39) in C. USE WITH CAUTION, IT DOES NOT GUARANTEE ENOUGH ENTROPY AND SAFETY!

## Overview

This program generates a 12-word seed, compliant with the BIP39 standard, for Bitcoin wallets. It uses a list of 2048 predefined words and selects 12 of them at random to create a seed. The randomness is sourced from a cryptographically secure pseudo-random number generator (CSPRNG) to ensure the seed's security.

## Dependencies

- OpenSSL: The program uses the `RAND_bytes` function from OpenSSL for cryptographically secure randomness.

## Compilation

To compile this program, you need to have GCC and OpenSSL library installed on your system. On a Unix-like system, you can compile the program with the following command:

```
make
```

## Downloading BIP-39 word list

```
wget https://raw.githubusercontent.com/bitcoin/bips/master/bip-0039/english.txt
```

Check for the file integrity:

```
echo "2f5eed53a4727b4bf8880d8f3f199efc90e58503646d9ff8eff3a2ed3b24dbda  english.txt" > english.sha256 && sha256sum -c english.sha256
```

## Running the Program

Before running the program, ensure you have the `english.txt` file in the same directory as your compiled executable. This file should contain the list of 2048 words used by the BIP39 standard, one word per line.

Run the program using:

```
./generate_seed
```

The program will print out a 12-word seed that you can use for your Bitcoin wallet.

## Security Note

This program is designed for educational purposes and should be carefully reviewed before being used in production systems. Ensure that the `english.txt` file is accurate and has not been tampered with. Additionally, the security of the generated seed relies on the proper functioning and implementation of the OpenSSL `RAND_bytes` function.

## Contributing

Contributions are welcome. Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the GPL License - see the [LICENSE](LICENSE) file for details.
