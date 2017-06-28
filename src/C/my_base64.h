#ifdef __cplusplus
extern "C" {
#endif
#ifndef MY_BASE64
#define MY_BASE64

int base64_encode(uint8_t* src, int len, uint8_t** dst);
int base64_decode(uint8_t* src, int len, uint8_t** dst);

#endif // TEMP_H
#ifdef __cplusplus
}
#endif


