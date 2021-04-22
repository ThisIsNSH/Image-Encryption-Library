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
    int col = 0;

    for(int i = 0; i < w; i++) {
        int k = key[i];
        for (int j = 0; j < h; j++) {
            outimage[(j*w)+k] = inimage[(j*w)+col];
        }
        col++;
    }
}
