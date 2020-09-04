#include <zlib.h>
#include <stdio.h>
#include "kseq.h"


KSEQ_INIT(gzFile, gzread)


int main(int argc, char *argv[])
{
	gzFile fp;
	kseq_t *seq;
	int l;


	if (argc < 2) {
		fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
		return 1;
	}


	// read in fastq
	fp = gzopen(argv[1], "r");
	seq = kseq_init(fp);
	while ((l = kseq_read(seq)) >= 0) {
		// HEADER
		printf("%c%s", seq->qual.l == seq->seq.l? '@' : '>', seq->name.s);
		if (seq->comment.l) printf(" %s", seq->comment.s);
		putchar('\n');

		// SEQUENCE
		printf("%s", seq->seq.s);
		putchar('\n');

		// QUALITY
		if (seq->qual.l != seq->seq.l) continue;
		printf("+\n");
		printf("%s", seq->qual.s);
		putchar('\n');
	}
	kseq_destroy(seq);
	gzclose(fp);

	return 0;
}
