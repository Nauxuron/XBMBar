#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

const int width = 104;

void parse_percentage(uint8_t *result, const int percentage) {
	int temp_per = percentage + 2;
        int counter = 0;

	while (temp_per >= 8) {
		result[counter] |= 0xff;
		temp_per -= 8;
                counter++;
	}

        result[counter] |= (1 << temp_per) - 1;
        result[12] |= 0xc0;
}

void print_xbm_file(uint8_t *bar, int height) {
        printf("%s %d\n", "#define xbmbar_width", width);
	printf("%s %d\n", "#define xbmbar_height", height);
	printf("%s\n", "static unsigned char xbmbar_bits[] = {");

	for (int i = 0; i < 2; i++) {
                printf("\t");
                for (int j = 0; j < width/8; j++) {
                    printf("%s, ", "0xff");
                }
                printf("\n");
	}

        for (int i = 0; i < height - 4; i++) {
                printf("\t");
		for (int j = 0; j < width/8; j++) {
			printf("0x%02x, ", bar[j]);
		}
		printf("\n");
	}
    
        printf("\t");
        for (int j = 0; j < width/8; j++) {
                printf("%s, ", "0xff");
        }
        printf("\n\t");
        for (int j = 0; j < (width/8 - 1); j++) {
                printf("%s, ", "0xff");
        }
        printf("0xff");
	printf(" %s\n", "};");
}

int main(int argc, char *argv[]) {
	char opt;
	int percentage, height = 8;
        int perc_flag = 0;
	while ((opt = getopt(argc, argv, "hp:y:")) != -1) {
		switch (opt) {
			case 'h':
				printf("xbmbar [-h]  [-y HEIGHT] [-p PERCENTAGE]\n");
				exit(0);
			case 'p':
				percentage = atoi(optarg);
                                perc_flag = 1;
				break;
                        case 'y':
                                height = atoi(optarg);
                                break;
		}
	}
        if (perc_flag != 1) {
            fprintf(stderr, "%s: %s", argv[0], "Try 'xbmbar -h' for more information.\n");
            exit(1);
        }
        if (percentage > 100 || percentage < 0) {
            fprintf(stderr, "%s: %s", argv[0], "Error: percentage must be between 0 and 100\n");
            exit(2);
        }
        if (height < 5) {
            fprintf(stderr, "%s: %s", argv[0], "Warning: height cannot be smaller than 5. Setting to default of 8\n");
            height = 8;
        }
        
	uint8_t *bar = calloc(1, width);
	parse_percentage(bar, percentage);
	print_xbm_file(bar, height);
        free(bar);
	return 0;
}
