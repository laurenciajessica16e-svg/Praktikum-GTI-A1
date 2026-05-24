#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

// Struktur untuk menyimpan data gambar BMP
struct Image {
    int width;
    int height;
    char* pixels;   // RGB data

    Image(int w, int h) : width(w), height(h) {
        pixels = new char[width * height * 3];
    }
    ~Image() {
        delete[] pixels;
    }
};

// Fungsi membaca file BMP
Image* loadBMP(const char* filename);

#endif
