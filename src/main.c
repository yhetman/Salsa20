/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/19 00:53:08 by yhetman                                  */
/*   Updated: 2021/11/07 23:59:10 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "salsa20.h"


static int
get_flags(int argc, char ** argv, FILE ** input, FILE ** output,
	FILE **key, FILE **nonce, bool * mode)
{
    int 	flag,
    		check_flags;

    check_flags = 0;
    
    while ((flag = getopt(argc, argv, "i:o:k:n:deh")) != -1)
    {
        switch (flag)
        {
            case 'i':
                *input = fopen(optarg, "rb");
                check_flags++;
                break;
            case 'o':
                *output = fopen(optarg, "wb");
                check_flags++;
                break;
            case 'k':
                *key = fopen(optarg, "rb");
                check_flags++;
                break;
            case 'n':
                *nonce = fopen(optarg, "rb");
                check_flags++;
                break;
            case 'd':
                *mode = false;
                break;
            case 'e':
                *mode = true;
                break;
            case 'h':
                printf("Usage:  ./salsa20 -i ./input_file -o ./output_file -k ./key_file -n ./nonce_file [flags]\n");
                return 1;

            case '?':
                fprintf(stderr, "%s unsuported flag.", optarg);
                return 1;
        }
    }
    if (check_flags < 4)
    {
        fprintf(stderr, "Needs to satisfy all parameters, use -h for help.\n");
        return 1;
    }

    return 0;
}



int
main(int argc, char **argv)
{
    FILE    *input,
            *output,
            *keyfile,
            *noncefile;
    bool    mode = true;
    size_t  rounds;
    uint8_t buff[64],
            kstream[64],
            cblock[64],
            key[32],
            nonce[8];
    uint64_t count = 0;
    
    if (get_flags(argc, argv, &input, &output, &keyfile,
        &noncefile, &mode) != 0)
       return 1;

    if ((rounds = fread(key, 1, 32, keyfile)) != 32)
    {
        printf("Error. Key has incorrect size\n");
        exit(1);
    }
    if ((rounds = fread(nonce, 1, 8, noncefile)) != 8)
    {
        printf("Error. Nonce has incorrect size\n");
        exit(1);
    }
    
    while ((rounds = fread(buff, 1, 64, input)))
    {
        salsa20(key, nonce, count, kstream);
        for (size_t i = 0; i < rounds; i++)
            cblock[i] = buff[i] ^ kstream[i];
        fwrite(cblock, 1, rounds, output);
        count++;
    };
    fclose(input);
    fclose(output);
    fclose(noncefile);
    fclose(keyfile);
    return 0;
}
