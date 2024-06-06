// Write a program to generate subkeys for user input key(bits) in DES

#include <stdio.h>
#include <stdlib.h>

int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void generateSubKeys(unsigned char* key, unsigned char subKeys[16][6]) {
    unsigned char permKey[7];
    unsigned char leftKey[4], rightKey[4];

    // Permuted Choice 1 (PC-1)
    for (int i = 0; i < 56; i++) {
        permKey[i / 8] |= (key[(PC1[i] - 1) / 8] >> (7 - ((PC1[i] - 1) % 8))) & 1;
        permKey[i / 8] <<= 1;
    }

    // Split permuted key into left and right halves
    for (int i = 0; i < 3; i++) {
        leftKey[i] = permKey[i];
        rightKey[i] = permKey[i + 3];
    }
    leftKey[3] = permKey[3] & 0xF0;
    rightKey[3] = (permKey[3] & 0x0F) << 4;
    rightKey[3] |= (permKey[4] & 0xF0) >> 4;

    // Generate 16 subkeys
    for (int i = 0; i < 16; i++) {
        // Circular left shift
        if (shiftBits[i] == 1) {
            unsigned char temp = leftKey[0];
            for (int j = 0; j < 3; j++)
                leftKey[j] = leftKey[j + 1];
            leftKey[3] = (leftKey[3] & 0x0F) << 4;
            leftKey[3] |= (temp & 0xF0) >> 4;

            temp = rightKey[0];
            for (int j = 0; j < 3; j++)
                rightKey[j] = rightKey[j + 1];
            rightKey[3] = (rightKey[3] & 0x0F) << 4;
            rightKey[3] |= (temp & 0xF0) >> 4;
        } else {
            unsigned char temp = leftKey[0];
            for (int j = 0; j < 3; j++)
                leftKey[j] = leftKey[j + 1];
            leftKey[3] = (leftKey[3] & 0x0F) << 4;
            leftKey[3] |= (leftKey[0] & 0xF0) >> 4;

            temp = rightKey[0];
            for (int j = 0; j < 3; j++)
                rightKey[j] = rightKey[j + 1];
            rightKey[3] = (rightKey[3] & 0x0F) << 4;
            rightKey[3] |= (rightKey[0] & 0xF0) >> 4;
        }

        unsigned char tempKey[7];
        tempKey[0] = leftKey[0];
        tempKey[1] = leftKey[1];
        tempKey[2] = leftKey[2];
        tempKey[3] = leftKey[3] | rightKey[0];
        tempKey[4] = rightKey[1];
        tempKey[5] = rightKey[2];
        tempKey[6] = rightKey[3];

        // Permuted Choice 2 (PC-2)
        for (int j = 0; j < 48; j++) {
            subKeys[i][j / 8] |= (tempKey[(PC2[j] - 1) / 8] >> (7 - ((PC2[j] - 1) % 8))) & 1;
            subKeys[i][j / 8] <<= 1;
        }
    }
}

int main() {
    unsigned char key[8];
    unsigned char subKeys[16][6];

    printf("Enter the 64-bit key: ");
    for (int i = 0; i < 8; i++)
        scanf("%hhx", &key[i]);

    generateSubKeys(key, subKeys);

    printf("Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%d: ", i + 1);
        for (int j = 0; j < 6; j++)
            printf("%02x ", subKeys[i][j]);
        printf("\n");
    }

    return 0;
}
