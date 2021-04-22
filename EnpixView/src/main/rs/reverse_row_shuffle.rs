#pragma version(1)
#pragma rs java_package_name(com.nsh.enpixview)

const float *inimage;
float *outimage;
const int *key;
const int *height;
const int *width;

void root(const int *v_in1) {
    int h = *height;
    int w = *width;
    int row = 0;

    for(int i = 0; i < h; i++) {
        int k = key[i];
        for (int j = 0; j < w; j++) {
            outimage[(k*w)+j] = inimage[(row*w)+j];
        }
        row++;
    }
}
