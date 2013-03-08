
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#define __STDC_CONSTANT_MACROS // ubuntu 12.04 workaround
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

AVFormatContext *fmt_ctx;
static const char *src_filename = "/home/rrizun/out.flv";

int main(int argc, char **argv) {

	av_register_all();


    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }

    printf("nbstreams=%d\n", fmt_ctx->nb_streams);

    /* retrieve stream information */
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

    AVStream *stream = fmt_ctx->streams[0];
    printf("nb_frames=%lu\n", stream->nb_frames);

    /* dump input information to stderr */
    av_dump_format(fmt_ctx, 0, src_filename, 0);

    AVPacket pkt;
    memset(&pkt, 0, sizeof(pkt));
    av_init_packet(&pkt);

//    /* read frames from the file */
    int count = 0;
    int total_pkt_size = 0;
    uint64_t pts = 0;
//    int stream_index = 0;
    while (av_read_frame(fmt_ctx, &pkt) >= 0) {
    	total_pkt_size += pkt.size;
//    	printf("%ld ", pkt.pos);
//        decode_packet(&got_frame, 0);

    	if (pkt.stream_index==0) // 0 is the video stream
    		pts = pkt.pts;

        av_free_packet(&pkt);
    }


    printf("\n");

	AVRational rational = fmt_ctx->streams[0]->time_base;

//	printf("last_pts=%lu\n", pts);
	printf("last_pts=%lum%lus\n", (pts/rational.den)/60, (pts/rational.den)%60);

	printf("total_pkt_size=%d\n", total_pkt_size);

	return 0;
}
