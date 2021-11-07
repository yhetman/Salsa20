/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   salsa20.h                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/19 00:53:23 by yhetman                                  */
/*   Updated: 2021/11/07 23:58:05 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SALSA20_H
# define SALSA20_H


# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>


# define 	ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))

# define 	WORDS2BYTES(w, a, b, c, d) ( \
			a = (uint8_t) w & 0xffffffff, \
			b = (uint8_t) (w >> 8) & 0xffffffff, \
			c = (uint8_t) (w >> 16) & 0xffffffff, \
			d = (uint8_t) (w >> 24) & 0xffffffff)

# define 	QR(a, b, c, d)(     \
    		b ^= ROTL(a + d, 7),    \
    		c ^= ROTL(b + a, 9),    \
    		d ^= ROTL(c + b, 13),    \
    		a ^= ROTL(d + c, 18))

# define 	littleendian(a, b, c,d) ( \
        	(uint32_t) a + \
        	((uint32_t) b << 8) + \
        	((uint32_t) c << 16) + \
        	((uint32_t) d << 24))


# define 	EXPA 0x61707865 
# define 	ND3 0x3320646e
# define 	BY2 0x79622d32
# define 	TEK 0x6b206574

# define 	ROUNDS 20

void		salsa20(uint8_t key[32], uint8_t nonce[8],
			uint64_t c, uint8_t kstream[64]);

#endif
