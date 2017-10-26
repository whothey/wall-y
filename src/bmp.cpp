#include "bmp.hpp"

void swapRB(unsigned char &b, unsigned char &r) {
    unsigned char x;
    x = r;
    r = b;
    b = x;
}

unsigned char* loadBMP_custom(const char * filename, unsigned int &width, unsigned int &height) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    //unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;
    // Open the file
    FILE * file;
    file = fopen( filename, "rb");
    if (!file) { printf("Image could not be opened\n"); return 0; };
    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return NULL;
    }
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }
    // Read ints from the byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
    // Create a buffer
    data = new unsigned char[imageSize];
    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);
    for (unsigned int i = 0; i < imageSize; i += 3) swapRB(data[i], data[i + 2]);
    //Everything is in memory now, the file can be closed
    fclose(file);
    return data;

}
