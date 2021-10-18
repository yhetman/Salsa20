/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/19 00:53:08 by yhetman                                  */
/*   Updated: 2021/10/19 00:53:10 by yhetman                                  */
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
                *input = fopen(optarg, "r");
                check_flags++;
                break;
            case 'o':
                *output = fopen(optarg, "w+");
                check_flags++;
                break;
            case 'k':
                *key = fopen(optarg, "r");
                check_flags++;
                break;
            case 'n':
                *nonce = fopen(optarg, "r");
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
	FILE 	*input,
			*output,
			*key,
			*nonce;
	bool	mode = true;
	//uint8_t	buff[BUFFER_SIZE];


    if (get_flags(argc, argv, &input, &output, &key, &nonce, &mode) != 0)
       return 1;
}
