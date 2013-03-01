
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
//#include <libavcodec/avcodec.h>
//#include <libavutil/avutil.h>
}

int main(int argc, char **argv) {

	av_register_all();

	printf("Hello, world! %s\n", avformat_license());
	printf("Hello, world! %s\n", avformat_configuration());
	return 0;
}
