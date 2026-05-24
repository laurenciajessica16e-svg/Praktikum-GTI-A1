#include "imageloader.h"
#include <fstream>
#include <iostream>
using namespace std;

Image* loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);

    if (!input.good()) {
        cout << "Cannot open image file: " << filename << endl;
        return NULL;
    }

    // Baca BMP header (54 bytes)
    char header[54];
    input.read(header, 54);

    // Ambil dimensi dari header
    int width  = *(int*)(header + 18);
    int height = *(int*)(header + 22);

    // Hitung padding (setiap row harus kelipatan 4 bytes)
    int bytesPerRow = ((width * 3 + 3) / 4) * 4;
    int paddingPerRow = bytesPerRow - (width * 3);

    Image* image = new Image(width, height);

    // BMP disimpan bottom-up, baca baris dari bawah ke atas
    for (int row = height - 1; row >= 0; row--) {
        for (int col = 0; col < width; col++) {
            int idx = (row * width + col) * 3;
            // BMP order: B, G, R ? ubah ke R, G, B
            char b, g, r;
            input.read(&b, 1);
            input.read(&g, 1);
            input.read(&r, 1);
            image->pixels[idx]     = r;
            image->pixels[idx + 1] = g;
            image->pixels[idx + 2] = b;
        }
        // Skip padding bytes
        input.ignore(paddingPerRow);
    }

    input.close();
    return image;
}
