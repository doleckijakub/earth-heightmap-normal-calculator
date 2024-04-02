#include <stdio.h>
#include <assert.h>

#include "stb_image.h"
#include "stb_image_write.h"

int main(int argc, const char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input heightmap> <output>\n", argv[0]);
		return 1;
	}

	const char *input  = argv[1];
	const char *output = argv[2];

	int w, h, n;
	unsigned char *in = stbi_load(input, &w, &h, &n, 1);
	unsigned char *out = calloc(w * h, 4);
	assert(n == 1 && "Not grayscale");

	int i = 0, j = 0;
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			out[i++] = 255;
			out[i++] = 0;
			out[i++] = 0;
			out[i++] = in[j++];
		}
	}

	stbi_image_free(in);

	stbi_write_png(output, w, h, 4, out, 4 * w);

	free(out);

}
