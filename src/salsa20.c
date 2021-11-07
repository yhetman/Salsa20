/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   salsa20.c                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/07 23:25:05 by yhetman                                  */
/*   Updated: 2021/11/07 13:32:06 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "salsa20.h"


static void
initstate_block(uint32_t key[8], uint32_t nonce[2],
	uint32_t posstream[2], uint32_t state[16])
{
    state[0]  = EXPA;   // "expa"
    state[1]  = key[0];
    state[2]  = key[1];
    state[3]  = key[2];
    state[4]  = key[3];
    state[5]  = ND3;    // "nd 3"
    state[6]  = nonce[0];
    state[7]  = nonce[1];
    state[8]  = posstream[0];
    state[9]  = posstream[1];
    state[10] = BY2;     // "2-by"
    state[11] = key[4];
    state[12] = key[5]; 
    state[13] = key[6];
    state[14] = key[7];
    state[15] = TEK;    // "te k"

}

static void
salsarounds(uint32_t x[16])
{
    QR(x[0], x[4], x[8], x[12]); // column 1
    QR(x[5], x[9], x[13], x[1]); // column 2
    QR(x[10], x[14], x[2], x[6]); // column 3
    QR(x[15], x[3], x[7], x[11]); // column 4

    QR(x[0], x[1], x[2], x[3]); // row 1
    QR(x[5], x[6], x[7], x[4]); // row 2
    QR(x[10], x[11], x[8], x[9]); // row 3
    QR(x[15], x[12], x[13], x[14]); // row 4
};

static void
salsa20_block(uint32_t out[16],  uint32_t in[16], uint8_t kstream[64])
{
    uint32_t    x[16];
    size_t      i;

    for (i = 0; i < 16; i++)
        x[i] = in[i];

    for (i = 0; i < ROUNDS; i += 2)
        salsarounds(x);
    
    for (i = 0; i < 16; i++)
        out[i] = x[i] + in[i];

    for (i = 0; i < 16; i++)
        WORDS2BYTES(out[i], kstream[i * 4], kstream[i * 4 + 1 ],\
        	kstream[i * 4 + 2], kstream[i * 4 + 3]);
}


static void
bytes2words(uint8_t *bytes, uint32_t *words,
		int byteslen)
{
    for (int i = 0; i < byteslen / 4; i++)
        words[i] = littleendian(bytes[4 * i], bytes[4 * i + 1],\
        	bytes[4 * i +2 ], bytes[4 * i + 3]);    
};


void
salsa20(uint8_t key8[32], uint8_t nonce8[8],
		uint64_t c, uint8_t kstream[64])
{
    uint32_t 	key[8],
             	nonce[2],
             	posstream[2],
             	state[16],
             	wblock[16];

    bytes2words(key8, key, 32);
    bytes2words(nonce8, nonce, 8);

    posstream[0] = c & 0xffffffff;
    posstream[1] = c >> 32;
    
    initstate_block(key, nonce, posstream, state);
    salsa20_block(wblock, state, kstream);
}
