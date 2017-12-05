#ifdef __cplusplus
extern "C" {
#endif
#ifndef _CHECKSUM_H_
#define _CHECKSUM_H_
#if (defined _MSC_VER) && (_MSC_VER < 1600)
#error "The C-MAVLink implementation requires Visual Studio 2010 or greater"
#endif
#include <stdint.h>
#define X25_INIT_CRC 0xffff
#define X25_VALIDATE_CRC 0xf0b8
#ifndef HAVE_CRC_ACCUMULATE
static inline void crc_accumulate(uint8_t data, uint16_t *crcAccum) {
        uint8_t tmp;
        tmp = data ^ (uint8_t)(*crcAccum &0xff);
        tmp ^= (tmp<<4);
        *crcAccum = (*crcAccum>>8) ^ (tmp<<8) ^ (tmp <<3) ^ (tmp>>4);
}
#endif
static inline void crc_init(uint16_t* crcAccum) { *crcAccum = X25_INIT_CRC; }
static inline uint16_t crc_calculate(const uint8_t* pBuffer, uint16_t length) {
        uint16_t crcTmp;
        crc_init(&crcTmp);
	while (length--) crc_accumulate(*pBuffer++, &crcTmp);
        return crcTmp;
}
static inline void crc_accumulate_buffer(uint16_t *crcAccum, const char *pBuffer, uint16_t length){
	const uint8_t *p = (const uint8_t *)pBuffer;
	while (length--)  crc_accumulate(*p++, crcAccum);
}
#endif
#ifdef __cplusplus
}
#endif
