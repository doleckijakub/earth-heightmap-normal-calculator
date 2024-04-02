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
	{
		int w, h, n;
		unsigned char *data = stbi_load(input, &w, &h, &n, 0);
		assert(n == 1 && "Not grayscale");

		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				
			}
		}

		stbi_image_free(data);
	}

	const char *output = argv[2];


}
